<?php

    // configuration
    require("../includes/config.php"); 
	// retrieve id
	$id = $_SESSION["id"];
	$rows = query("SELECT * FROM stocks WHERE id = $id");
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
	// if user reached page via GET (hasn't sold yet)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
		// render selling form
		render("sell_form.php", ["title" => "Sell", "positions" => $positions]);
    }
	// if user reached via POST (has placed a sell order)
	else if($_SERVER["REQUEST_METHOD"] == "POST")
	{
		if(empty($_POST["symbol"]) || empty($_POST["amount"]))
		{
			apologize("You have to specify company and amount in order to sell.");
		}
		else
		{
			foreach($positions as $position)
			{
				// if the user chose a valid symbol and sold less (or equal) than 					
				// she/he had, make the operation.
				if ($position["symbol"] == $_POST["symbol"])
				{
					$money = $_POST["amount"]*$position["price"];
					$sym = $_POST["symbol"];					
					// if she/he sold everything					
					if ($position["shares"] == $_POST["amount"])
					{
						query("DELETE FROM stocks WHERE id = $id AND symbol = '".$sym."'");	
						query("UPDATE users SET cash = cash + $money WHERE id = $id");						
						query("INSERT INTO history (id, date, action, symbol, amount, price) VALUES( $id, NOW(), 'SELL', '". $sym ."', ".$_POST["amount"].", ".$position['price'].")");
						// render sold page
						render("sold.php", ["title" => $position['symbol']." Stocks Sold", "left" => 0, "position" => $position]);
					}
					// only a fraction of the shares owned.
					else if ($position["shares"] > $_POST["amount"] && $_POST["amount"] > 0)
					{
						$left = $position["shares"] - $_POST["amount"];					
						query("UPDATE stocks SET shares = $left WHERE id = $id AND symbol = '".$sym."'");
						query("UPDATE users SET cash = cash + $money WHERE id = $id");
						query("INSERT INTO history (id, date, action, symbol, amount, price) VALUES($id, NOW(), 'SELL', '". $sym ."', ".$_POST["amount"].", ".$position['price'].")");
						// render sold page
						render("sold.php", ["title" => $position['symbol']." Stocks Sold", "left" => $left, "position" => $position]);
					}
					// tried to sell more than she/he had
					else if ($position["shares"] < $_POST["amount"] && $_POST["amount"] > 0)
					{
						apologize("Amount chosen exceeds amount in posession.");
					}
					// tried to sell a negative number of shares.				
					else if ($_POST["amount"] < 0)
					{
						apologize("Amount must be a positive value.");
					}
					// unexpected error
					else
					{
						apologize("Error in transaction: invalid input. Nothing has been sold. Please check submitted form.");
					}

				}
			}
		}

	}

	
	

?>
