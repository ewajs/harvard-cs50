<?php

    // configuration
    require("../includes/config.php"); 
	
	// retrieve id
	$id = $_SESSION["id"];
	
	$rows = query("SELECT * FROM stocks WHERE id = $id");	
	$aux = query("SELECT cash FROM users WHERE id = $id");
	$cash = $aux[0]["cash"];	
	$positions = [];
	foreach ($rows as $row)
	{
		$stock = lookup($row["symbol"]);
		if ($stock["name"] != "N/A")
		{
		    $positions[] = [
		        "name" => $stock["name"],
		        "price" => $stock["price"],
		        "shares" => $row["shares"],
		        "symbol" => $row["symbol"]
		    ];
		}
	}
    // render portfolio
    render("portfolio.php", ["title" => "Portfolio", "positions" => $positions, "cash" => $cash]);

?>
