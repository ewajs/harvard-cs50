<div>
    <table class="table table-striped">
	<tr>
		<th>Transaction ID</th>
		<th>Date</th>
		<th>Action</th>
		<th>Company Name</th>
		<th>Shares</th>
		<th>Price (per share)</th>
		<th>Net account change</th>
	</tr>
    <?php
        foreach ($rows as $row)
        {
            print("<tr>");
            print("<td>" . $row["transid"] . "</td>");
            print("<td>" . $row["date"] . "</td>");
            print("<td>" . $row["action"] . "</td>");
            print("<td>" . $row["symbol"] . "</td>");
            print("<td>" . $row["amount"] . "</td>");
            print("<td>$" . $row["price"] . "</td>");
			if($row["action"] == "BUY")
			{
				print("<td>-$" . $row["price"]*$row["amount"] . "</td>");
			}
			else if($row["action"] == "SELL")
			{
				print("<td>+$" . $row["price"]*$row["amount"] . "</td>");
			}
            print("</tr>");
        }
    ?>
</table>
</div>

