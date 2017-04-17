<HTML>
<BODY>
<FORM action="php12.php" method="post">
Year: <input type="text" name="year">
<input type="submit">
</form>

<?php
include "php12.php";    # Processing code moved to php12

process(date("Y"));     # Start from the current year on initialization

if (array_key_exists("year", $_POST)) {
        process($_POST["year"]);
}

?>
</BODY>
</HTML>
<?php
