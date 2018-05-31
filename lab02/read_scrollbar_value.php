<html>
<head>
  <title>Read xml scrollbar value</title>
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
  $file = $base."/sliderValue.txt";
  //printf("<p>DEBUG: parsed \$file as %s</p>",$file);
  
  // Get the old count value
  $fileDataLst = file($file);
  $count = (float) $fileDataLst[0];
  printf("<p><xml><scrollbarValue>%f</scrollbarValue></xml></p>", $count);
  
?>
</body>
</html>