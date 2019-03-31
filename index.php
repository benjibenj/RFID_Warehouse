<?php
$file = fopen('files/RFIDtrace.txt','r');
?>
<!doctype html>
<html lang="en">
  <head>
    <!-- Required meta tags -->
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">

    <!-- Bootstrap CSS -->
    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css" integrity="sha384-MCw98/SFnGE8fJT3GXwEOngsV7Zt27NXFoaoApmYm81iuXoPkFOJwJ8ERdknLPMO" crossorigin="anonymous">
      <link rel="stylesheet" href="css/style.css" type="text/css">
      <title>RFID</title>
  </head>
  <body>
  </br>
  </br>
  <center>
      <h2>Detected Tags</h2>
  </center>
  </br>
  </br>
    <div class="container">
        <table>
            <tr>
                <th>Date</th>
                <th>HH:MM:SS</th>
                <th>Frequency</th>
                <th>Localisation</th>
                <th>Product</th>
                <th>RSSI</th>
            </tr>
            <?php
            $file = fopen('files/Detected_products.txt','r');
                while ($line = fgets($file)) {
                    if (strlen($line)>1){
                        echo "<tr>";
                        $parts = explode(' ',$line);
                        echo "<td>$parts[0]</td>";
                        echo "<td>$parts[1]</td>";
                        echo "<td>$parts[4]</td>";
                        echo "<td>$parts[5]</td>";
                        echo "<td>";
                        if ($parts[6] == 'E20000172211013513608FEB') {
                            echo "<img src='files/img/glacevanille.jpg' height=\"42\" width=\"42\" >";
                        }
                        if ($parts[6] == 'E20000172211014813608FC1') {
                            echo "<img src='files/img/blocnotes.jpg' height=\"42\" width=\"42\">";
                        }
                        if ($parts[6] == 'E20000172211015413608FC4') {
                            echo "<img src='files/img/cereales.jpg' height=\"42\" width=\"42\">";
                        }
                        echo $parts[6];
                        echo "</td>";
                        echo "<td>$parts[7]</td>";
                        echo "</tr>";
                    }
                }
            ?>
        </table>
    </div>
    <!-- Optional JavaScript -->
    <!-- jQuery first, then Popper.js, then Bootstrap JS -->
    <script src="https://code.jquery.com/jquery-3.3.1.slim.min.js" integrity="sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo" crossorigin="anonymous"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.3/umd/popper.min.js" integrity="sha384-ZMP7rVo3mIykV+2+9J3UJ46jBk0WLaUAdn689aCwoqbBJiSnjAK/l8WvCWPIPm49" crossorigin="anonymous"></script>
    <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/js/bootstrap.min.js" integrity="sha384-ChfqqxuZUCnJSK3+MXmPNIyE6ZbWh2IMqE241rYiqJxyMiZ6OW/JmZQ5stwEULTy" crossorigin="anonymous"></script>
  </body>
</html>
