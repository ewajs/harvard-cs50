<form action="sell.php" method="post">
    <fieldset>
        <div class="form-group">
            <select class="form-control" name="symbol">
				<?php
					foreach($positions as $position)
					{
						print("<option value = '".$position["symbol"]."'>".$position["name"]." (".$position["symbol"].") at $".number_format($position["price"],2)." each (".$position["shares"]." shares held)</option>");
					}
				?>
			</select>
        </div>
        <div class="form-group">
            <input autofocus class="form-control" name="amount" placeholder="Amount" type="text"/>
        </div>
        <div class="form-group">
            <button type="submit" class="btn btn-default">Sell</button>
        </div>
    </fieldset>
</form>

