<?php

    require(__DIR__ . "/../includes/config.php");
    // numerically indexed array of places
	//$search = explode(",", $_GET["geo"]);
	$places = query("SELECT * FROM places WHERE 
instr(concat_ws(', ',country_code, postal_code, place_name, admin_name1,
admin_code1, admin_name2, admin_code2),?)>0;",$_GET["geo"]);	
	/*for($i = 0; $i < count($search); $i++)
	{
		trim($search[$i]);    
		$aux = query("SELECT * FROM places WHERE MATCH(country_code, postal_code, place_name, admin_name1, admin_code1, admin_name2, admin_code2) AGAINST (?);", $search[$i]);
		$places	= array_merge($places, $aux);
	}*/
    // output places as JSON (pretty-printed for debugging convenience)
    header("Content-type: application/json");
    print(json_encode($places, JSON_PRETTY_PRINT));

?>


