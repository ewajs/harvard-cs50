<p class="lead text-danger">
    Sorry!
</p>
<p class="text-danger">
    <?= htmlspecialchars($message) ?>
</p>

<?php 
	if(isset($_SESSION["returnflag"]))
	{
		print("<a href='buy.php'>Back</a>");
		unset($_SESSION["returnflag"]);
	}else
	{
		print("<a href='javascript:history.go(-1);'>Back</a>");
	}
?>
