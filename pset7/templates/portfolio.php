<div>
    <table class="table table-striped">
	<tr>
		<th>Symbol</th>
		<th>Company Name</th>
		<th>Shares</th>
		<th>Price (per share)</th>
		<th>Total</th>
	</tr>
    <?php
	$total = 0;
        foreach ($positions as $position)
        {
            print("<tr>");
            print("<td>" . $position["symbol"] . "</td>");
            print("<td>" . $position["name"] . "</td>");
            print("<td>" . $position["shares"] . "</td>");
            print("<td>$" . number_format($position["price"], 2) . "</td>");
            print("<td>$" . number_format($position["price"]*$position["shares"], 2) . "</td>");
			$total = $total + ($position["price"]*$position["shares"]);
            print("</tr>");
        }
    ?>
	<tr>
		<td colspan ="4">Cash</td>
		<td>$<?= print(number_format($cash,2));?></td>
	</tr>
	<tr>
		<td colspan ="4">Total (cash + shares)</td>
		<td>$<?= print(number_format($cash + $total,2));?></td>
	</tr>
</table>
</div>
<div>
    <a href="logout.php">Log Out</a>
</div>
