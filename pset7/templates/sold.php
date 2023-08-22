<?php
	print("You've sold <strong>".($position["shares"] - $left)." shares of ".$position["name"]." (".$position["symbol"].") </strong> at a total profit of <strong>$" .(($position["shares"] - $left)*$position["price"]) . "</strong>. <strong>You have $left remaining stocks</strong>. Go to <a href='/index.php'>portfolio</a> for full detail.");
?>
