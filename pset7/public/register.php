<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("register_form.php", ["title" => "Register"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {

		// validate submission
        if (empty($_POST["username"]))
        {
            apologize("You must provide your username.");
        }
        else if (empty($_POST["password"]))
        {
            apologize("You must provide your password.");
        }
		else if (empty($_POST["mail"]))
		{
			apologize("You must provide an email address.");
		}
		else if ($_POST["password"] != $_POST["confirmation"])
        {
            apologize("Password and confirmation must coincide.");
        }
		else if ($_POST["mail"] != $_POST["conf"])
		{
			apologize("e-mails do not match.");
		}
		else if (!filter_var($_POST["mail"], FILTER_VALIDATE_EMAIL))
		{
			apologize("e-mail provided is not valid.");
		}
	    else
	    {
			$res = query("INSERT INTO users (username, hash, cash, mail) VALUES(?, ?, 10000.00, ?)", $_POST["username"], crypt($_POST["password"]), $_POST["mail"]);
		    if ($res === false)
		    {
			    apologize("Username already taken. Choose another.");
		    }
            else
            {
                $rows = query("SELECT LAST_INSERT_ID() AS id");
                $_SESSION["id"] = $rows[0]["id"];
                redirect("/");
            }
            
	    }

	
    }

?>
