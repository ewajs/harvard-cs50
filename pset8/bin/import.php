#!/usr/bin/env php
<?php
	require_once("../includes/functions.php");
    $path = $argv[1];

	if(!is_readable($path))
	{
		exit("Error reading file.\n");
	}

	$file = fopen($path,"r");
	$row = 0;
	while(NULL != ($data = fgetcsv($file, 1000, "	")))
	{
		query("INSERT INTO places (country_code, postal_code, place_name, admin_name1, admin_code1, admin_name2, admin_code2, admin_name3, admin_code3, latitude, longitude, accuracy) VALUES (?,?,?,?,?,?,?,?,?,?,?,?);",$data[0], $data[1],$data[2], $data[3],$data[4], $data[5],$data[6], $data[7],$data[8], $data[9],$data[10], $data[11]);
	}
	
	fclose($file);

?>
