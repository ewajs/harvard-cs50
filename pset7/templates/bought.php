<?php
	print("You've bought <strong>".$amount." shares of ".$name." (".$symbol.") </strong> at a total cost of <strong>$" .number_format($amount*$price,2) . "</strong>. Go to <a href='/index.php'>portfolio</a> for full detail.");
?>
