<?php
	// user already has shares of the company in question.	
	print("The price for a share of <strong>$name (".$symbol.") is $price</strong>. "); 	
	if ($owned == 1)
	{
		print("You <strong>already have $shares shares</strong>.</br>");
	}
	else
	{
		print("You don't currently own any shares of this company.</br>");
	}
	print("You currently have <strong>$".number_format($cash,2)." in cash</strong>. You can buy a <strong> maximum of ".number_format($max,0)." shares</strong>.</br></br></br>");
?>
<div>
<form action="buy.php" method="post">
    <fieldset>
        <div class="form-group">
            <input autofocus class="form-control" name="amount" placeholder="Amount" type="text"/>
        </div>
        <div class="form-group">
            <button type="submit" class="btn btn-default">Buy shares</button>
        </div>
    </fieldset>
</form>
</div>

