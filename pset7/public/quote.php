<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("quote_form.php", ["title" => "Quote"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
         // validate submission
        if (empty($_POST["symbol"]))
        {
            apologize("You must provide the Stock Symbol you want.");
        }
        else
        {
            $s = lookup($_POST["symbol"]);
            if ($s["name"] === "N/A")
            {
                apologize("Symbol not found in database.");
            }
            else
            {
                $s["title"] = $s["symbol"] . " Stock Price";
                render("quote_response.php", $s);
            }        
        }
		

	
    }

?>
