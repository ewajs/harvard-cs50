<?php

    // configuration
    require("../includes/config.php"); 
	// retrieve id
	$id = $_SESSION["id"];
	
	// if user reached page via GET (hasn't bought yet)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
		$_SESSION["phase"] = 1;		
		// render selling form
		render("buy_form1.php", ["title" => "buy"]);
    }
	// if user reached via POST (has placed a sell order)
	else if($_SERVER["REQUEST_METHOD"] == "POST")
	{
		// if user has selected a symbol (and not specified amount yet)
		if($_SESSION["phase"] == 1)
		{
			$s = lookup(strtoupper($_POST["symbol"]));
            if ($s["name"] === "N/A")
            {
                apologize("Symbol not found in database.");
            }
            else
            {
                $s["title"] = $s["symbol"] . " Stock Price";
				$s["owned"] = 0;
				$rows = query("SELECT * FROM stocks WHERE id = $id");
				foreach ($rows as $row)
				{
					if ($row["symbol"] == $s["symbol"])
					{
						$s["owned"] = 1;
						$s["shares"] = $row["shares"];
					}
				}
                
				$rows = query("SELECT * FROM users WHERE id = $id");
				// as only one must have been found.
				$row = $rows[0];
				$s["cash"] = $row["cash"];
				$_SESSION["phase"] = 2;
				$maxshares = round($s["cash"]/$s["price"]);
				$s["max"] = $maxshares;
				$_SESSION["data"] = $s;				
				// render second part
				render("buy_form2.php", $s);			
			}        
		}
		else if($_SESSION["phase"] == 2)
		{
			$data = $_SESSION["data"];
			$id = $_SESSION["id"];
			unset($_SESSION["data"]);
			$max = $data["max"];
			$symbol = $data["symbol"];
			$price = $data["price"];
			$amount = $_POST["amount"];
			$data["amount"] = $amount;
			unset($_SESSION["phase"]);
			//apologize("Amount: $amount - Price: $price - Symbol: $symbol - Amount*Price: ".$amount*$price);
			// positive integer
			if (preg_match("/^\d+$/", $amount) === false)
			{
				$_SESSION["returnflag"] = 1;				
				apologize("Amount of shares to buy must be a positive integer.");
			}
			// if amount is positive and valid
			else if ($amount < $max)
			{
				query("INSERT INTO stocks (id, symbol, shares) VALUES($id, '$symbol', $amount) ON DUPLICATE KEY UPDATE shares = shares + $amount");
				query("UPDATE users SET cash = (cash - ".$amount*$price. ") WHERE id = $id");
				query("INSERT INTO history (id, date, action, symbol, amount, price) VALUES($id, NOW(), 'BUY', '$symbol', $amount, $price)");
				$data["title"] = "Shares Bought!";				
				
				// notify via email

				$rows = query("SELECT * FROM users WHERE id = $id");

       			// if we found user, send mail
        		if (count($rows) == 1)
       			{
            		// first (and only) row
            		$row = $rows[0];
					$mail = $row["mail"];
					if(!emailNotify($mail,$data))
					{
						$_SESSION["returnflag"] = 1;						
						apologize("MAIL ERROR");
					}
					else
					{
						render("bought.php", $data);
					}
				}

			}
			else if ($amount > $max)
			{
				$_SESSION["returnflag"] = 1;				
				apologize("Can't buy that much shares with current cash.");
			}
			else
			{
				$_SESSION["returnflag"] = 1;
				apologize("Error in transaction: invalid input. Nothing has been bought. Please check submitted form.");
			}
		}

	}

	
	

?>
