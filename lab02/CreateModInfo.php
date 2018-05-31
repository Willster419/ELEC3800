<?php
ini_set( 'display_errors', true );
error_reporting( E_ALL );
set_time_limit(0);
date_default_timezone_set('Europe/Zurich'); /* notwendig ab PHP 5.3, sonst Warnung */

// clearFlagTime (wann darf vom script automatisch der process neu gestartet werden und das alte Flag gelöscht)
$clearFlagTime = 1 * 30 * 60;			// 1 Stunde * 60 Minuten * 60 Sekunden

//Debug variables, $i and $k are for recursive use
function DebugDisplayVar($input, $name = "Debug", $i = "0", $k = array("Error")){
	if(is_array($input)) {
		foreach ($input as $i => $value){
			$temp = $k;
			$temp[] = $i;
			DebugDisplayVar($value, $name, $i, $temp);
		}
	} else { //if not array
		echo "$".$name; //[$k]
		foreach ($k as $i => $value){
			if($value !=="Error") {
				echo "[$value]";
			}
		}
		echo " = $input<br>";
	}
}

// https://stackoverflow.com/questions/19816438/make-var-dump-look-pretty
function DebugDumpColored($data) {
	highlight_string("<?php\n\$data =\n" . var_export($data, true) . ";\n?>");
}

// https://stackoverflow.com/questions/19816438/make-var-dump-look-pretty
function DebugDumpSimple($data) {
	echo '<pre>' . var_export($data, true) . '</pre>';
}

function formatSizeUnits($bytes) {
	if ($bytes >= 1073741824)
	{
		$bytes = number_format($bytes / 1073741824, 2) . ' GB';
	}
	elseif ($bytes >= 1048576)
	{
		$bytes = number_format($bytes / 1048576, 2) . ' MB';
	}
	elseif ($bytes >= 1024)
	{
		$bytes = number_format($bytes / 1024, 2) . ' kB';
	}
	elseif ($bytes > 1)
	{
		$bytes = $bytes . ' bytes';
	}
	elseif ($bytes == 1)
	{
		$bytes = $bytes . ' byte';
	}
	else
	{
		$bytes = '0 bytes';
	}
	return $bytes;
}

// http://php.net/manual/de/function.filesize.php
function find_filesize($file) {
    if(substr(PHP_OS, 0, 3) == "WIN")
    {
        exec('for %I in ("'.$file.'") do @echo %~zI', $output);
        $return = $output[0];
    }
    else
    {
        $return = filesize($file);
    }
    return $return;
}

function url_exists($url) {
	$file_headers = @get_headers($url);
	if($file_headers[0] == 'HTTP/1.1 404 Not Found') {
		return FALSE;
	}
	else {
		return TRUE;
	}
}

function AddTrailingSlash($str) {
	return $str .= (substr($str, -1) == '/' ? '' : '/');
}

function RemoveTrailingSlash($str) {
	return rtrim($str, '/');				// remove trailing slash if one is there
}

function RemoveAheadSlash($str) {
	return ltrim($str, '/');				// remove ahead shlash if one is there
}

function ReplaceBackWithSlash($str) {
	return str_replace('\\', '/', $str);	// replace all backslash with slash
}

function removeFOOFilesInFolder($str) {
	// Zählervariable für Meldung gelöschter FOO Dateien
	$FOOcounter = 0;
	foreach (glob("FOO*") as $filename) {
		++$FOOcounter;
		unlink($filename);
	}
	if ($FOOcounter > 0) {
		echo "removed $FOOcounter old FOO file(s)<br />\n";
	}
	return $FOOcounter;
}

function getHighestVersion($arr) {
	usort($arr, 'version_compare');
	return (string)end($arr);
}

echo "script is started (" . date("d.m.Y H:i:s") . ")<br /><br />\n";
$scriptstarttime = microtime(true);

$xmlFilename = "modInfo.xml";
$compressedFilename = "modInfo.dat";

$base = "/home/eueijvmj/wotmods.relhaxmodpack.com";
$basisWoTMods = AddTrailingSlash($base) . "WoT";
$baseFolderModPack = AddTrailingSlash($base) . "RelhaxModpack";
$baseFolderDeveloperSelections = AddTrailingSlash($baseFolderModPack) . "Resources/developerSelections";
$baseFolderNameModInfoXml = AddTrailingSlash($baseFolderModPack) . "Resources/modInfo";
$baseFolderNameManagerInfoXml = AddTrailingSlash($baseFolderModPack) . "Resources/managerInfo";

$folderSelections = opendir($baseFolderDeveloperSelections);
$dataSelection = array ();
while($entry = readdir ($folderSelections)) {
	$completeWithPath = AddTrailingSlash($baseFolderDeveloperSelections) . $entry;
	if(($entry <> "..") and ($entry <> "selections.xml") and (substr($entry, 0, 4) <> "test") and (strtolower(substr($entry,-4)) == strtolower(".xml")) and ($entry <> ".") and (substr($entry,0,1) <> ".")) {
		try
		{
			// load the personal selection xml file
			$xml_data_as_object = simplexml_load_file($completeWithPath);
			// write the attributes of "mods" to an array
			$xmlModsAttribArr = $xml_data_as_object->attributes();
			// check if attribute "displayName" exists
			if (isset($xmlModsAttribArr["displayName"])) {
				// yes, use it as displayName
				$xmlDisplayName = $xmlModsAttribArr["displayName"];
			} else {
				// no, use the config xml filename as displayName
				$xmlDisplayName = substr($entry,0,strlen($entry)-4);
			}
			// InternalName is the xml-config-filename
			$xmlInternalName = $entry;
			// write all readed informations to a new array record at $dataSelection
			array_push($dataSelection,
				array(
					'internalName' => $xmlInternalName,
					'displayName' => $xmlDisplayName,
					'date' => $xmlModsAttribArr["date"]
				)
			);
			echo "selection <strong>$xmlDisplayName</strong> ($xmlInternalName) parsed<br />";
		} catch (Exception $e) {
			echo "Error at xml file: $entry =>",  $e->getMessage(), "\n";
		}
	}
}
// debug print the data structure of $dataSelection
// DebugDisplayVar($dataSelection, "dataSelection");
echo "<br />";

$existingWotFolderVersion = array ();
$verzeichnis = opendir($basisWoTMods);
while($eintrag = readdir ($verzeichnis)) {
	$completeWithPath = AddTrailingSlash($basisWoTMods) . $eintrag;
	if(is_dir($completeWithPath) and ($eintrag <> "..") and ($eintrag <> "ModPictures") and ($eintrag <> ".") and (substr($eintrag,0,1) <> ".")) {
		$wotFolderVersion = $eintrag;
		array_push($existingWotFolderVersion, $eintrag);
		$xml = simplexml_load_file(AddTrailingSlash($baseFolderNameManagerInfoXml)."supported_clients.xml");  // Load XML File Need to add IF Statment to create if does not exist
		$wotLiveVersion = getHighestVersion($xml->xpath('version[@folder="' . $wotFolderVersion . '"]'));
		if ($wotLiveVersion == "")
		{
			echo "<strong>skip WoT version folder $wotFolderVersion, because WoT Live version is not assigned in supported_clients.xml</strong><br />";
			continue;
		}
		$localModInfoFile = AddTrailingSlash($completeWithPath) . $xmlFilename;
		$fileToCopy = AddTrailingSlash($baseFolderNameModInfoXml) . "modInfo_$wotLiveVersion.xml";
		if (file_exists($fileToCopy))
		{
			if (copy ($fileToCopy, $localModInfoFile)) {
			} else {
				echo "<strong>WARNING</strong>. Failed to copy modInfo_$wotLiveVersion.xml<br /><strong>creating $compressedFilename canceled</strong><br />";
				continue;
			}
		} else {
			echo "<strong>WARNING</strong>. Failed to copy modInfo_$wotLiveVersion.xml (not existing)<br /><strong>creating $compressedFilename canceled</strong><br />";
			continue;
		}
		// https://stackoverflow.com/questions/16480589/adding-nodes-to-existing-xml
		$xml = simplexml_load_file($localModInfoFile);  // Load XML File Need to add IF Statment to create if does not exist
		// add the folder information to the root element
		$xml['onlineFolder'] = $wotFolderVersion;
		// create the "selections" group with the internal names
		$result = $xml->addchild('selections'); // Ignore Root NODE and Add Child selections
		// create zip file handle
		$zip = new ZipArchive();
		// create the Zip file
		if ($zip->open(AddTrailingSlash($completeWithPath) . $compressedFilename, ZipArchive::CREATE) === TRUE) {
			// write the selections xml-file-informations to the xml data string
			foreach ($dataSelection as $record) {
				$att = $result->addChild('internalName', $record['internalName']);
				$att->addAttribute('displayName', $record['displayName']);
				$att->addAttribute('date', $record['date']);
				// add xml-config-file to the archive
				$zip->addFile(AddTrailingSlash($baseFolderDeveloperSelections) . $record['internalName'], $record['internalName']);
			}
			$data = $xml->asXML();
			libxml_use_internal_errors(true);
			$doc = new DOMDocument('1.0','utf-8');
			$doc->preserveWhiteSpace = false;
			if (!$doc->loadxml($data)) {
				$errors = libxml_get_errors();
				DebugDumpColored($errors);
			}
			$doc->formatOutput = true;
			// save changes to 
			$doc->save($localModInfoFile);
			// add modInfo.xml to the Archive
			$zip->addFile($localModInfoFile, $xmlFilename);
			// close the Archive
			$zip->close();
			// delete temp created modInfo.xml
			unlink($localModInfoFile);
		} else {
			echo "<strong>WARNING</strong>. Failed to create compressed $compressedFilename<br />WoT v$wotLiveVersion (folder $wotFolderVersion) <strong>NOT</strong> usable!<br />";
			break;
		}
		echo "WoT v$wotLiveVersion (folder $wotFolderVersion) done<br />";
	}
}
closedir($verzeichnis);

echo "<br />\n";

foreach ($existingWotFolderVersion as $x) {
	echo "$x<br />\n";
	// ++$FOOcounter;
	// unlink($filename);
}


// Calculate the script runtime
$scriptruntime = microtime(true) - $scriptstarttime;
$scriptruntimestr = number_format ($scriptruntime, 2);

echo "script is done ! (" . date("d.m.Y H:i:s") . ") Total runtime: $scriptruntimestr sec.";
// to be sure, no malicious php code could be appended to this file and executed, so leave it with Exit
Exit;
?>
