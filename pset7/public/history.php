<?php

    // configuration
    require("../includes/config.php"); 
	// retrieve id
	$id = $_SESSION["id"];
	$rows = query("SELECT * FROM history WHERE id = $id");
	// render history page
	render("showhist.php", ["title" => "History", "rows" => $rows]);
	
?>
