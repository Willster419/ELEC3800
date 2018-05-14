<html>
<head>
  <title>Write passed in scrollbar value to file</title>
</head>

<body>
<?php
  //useful script stuff
  ini_set( 'display_errors', true );//set the value to display all errors, helpfull for debugging
  error_reporting( E_ALL );//report all errors
  set_time_limit(0);//infinite timeout
  date_default_timezone_set('America/New_York'); /* notwendig ab PHP 5.3, sonst Warnung */
  
  //starting the script...
  //echo "script is started (" . date("d.m.Y H:i:s") . ")<br /><br />";
  printf("<p>script is started (\"%s\")</p>",date("d.m.Y H:i:s"));
  $base = "/home/eueijvmj/memes.relhaxmodpack.com/SchoolProjects/ELEC3800_WebApp";
  //printf("<p>DEBUG: parsed \$base as %s</p>",$base);
  $file_to_write = $base."/sliderValue.txt";
  //printf("<p>DEBUG: parsed \$file_to_write as %s</p>",$file_to_write);
  
  //get the value passed into this HTTP GET request
  $wrVal=$_GET["wrVal"];
  printf("<p>parsed wrVal as %d</p>",$wrVal);

  //write a value to the file
  printf("writing value to disk...");
  $bytesWrote = file_put_contents($file_to_write,$wrVal);
  printf("<p>wrote %d bytes to store %f in the file %s </p>", $bytesWrote, $wrVal, $file_to_write );
  printf("<p>script is done (\"%s\")</p>",date("d.m.Y H:i:s"));
?>
</body>
</html>