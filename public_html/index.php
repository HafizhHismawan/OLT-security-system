<!doctype html>
<html lang="en">
  <head>
    <!-- Required meta tags -->
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">

    <!-- Bootstrap CSS -->
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css" integrity="sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm" crossorigin="anonymous">

    <title>miniOlt Security System</title>

    <script type="text/javascript" src="jquery/jquery.min.js"></script>
    <!-- load otomatis / realtime -->
    <script type="text/javascript">
      $(document).ready(function() {
        setInterval( function() {
          $("#cektandes").load("cektandes.php");
          $("#cekkapasan").load("cekkapasan.php");
          $("#cekkalianak").load("cekkalianak.php");

        }, 1000 );

      } );
    </script>


  </head>
  <body>
    <div class="container" style="text-align: center; margin-top:150px; font: size 20px;">
          <h2>Monitoring Mini OLT secara Real-time</h2>

        
        <div style="display: flex; margin-top:10px;">

          <!-- menampilkan status mini olt tandes -->
          <div class="card text-center" style="width:33.33%;">

            <div class="card-header" style="font-size:20px; font-weight:bold; background-color: red; color:white;">
                Mini OLT SBU
            </div>
            <div class="card-body">
               <h1> <span id="cektandes">  </span> </h1>
            </div>
           
          </div>
            <!--akhir menampilkan-->

          <!-- menampilkan status mini olt Kapasan -->
          <div class="card text-center" style="width:33.33%;">

            <div class="card-header" style="font-size:20px; font-weight:bold; background-color:red; color:white;">
                Mini OLT Kapasan
            </div>
            <div class="card-body">
               <h1> <span id="cekkapasan">  </span> </h1>
            </div>   
          </div>
            <!--akhir menampilkan-->

          <!-- menampilkan status mini olt Kalianak -->
          <div class="card text-center" style="width:33.33%;">
            <div class="card-header" style="font-size:20px; font-weight:bold; background-color:red; color:white;">
                Mini OLT Kalianak
            </div>
            <div class="card-body">
               <h1> <span id="cekkalianak">  </span> </h1>   
            </div>
          </div>
            <!--akhir menampilkan-->

        </div>

        <!-- logo kita -->
        <div class="container" style="margin-top:15px;"></div>
          <img src="images/telkom.png" width="144" height="80" align="left">
          <img src="images/pens.png" width="160" height="80" align="left">

    </div>
      


    <!-- Optional JavaScript -->
    <!-- jQuery first, then Popper.js, then Bootstrap JS -->

<!--    <script src="https://code.jquery.com/jquery-3.2.1.slim.min.js" integrity="sha384-KJ3o2DKtIkvYIK3UENzmM7KCkRr/rE9/Qpg6aAZGJwFDMVNA/GpGFF93hXpG5KkN" crossorigin="anonymous"></script>
-->
    <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.12.9/umd/popper.min.js" integrity="sha384-ApNbgh9B+Y1QKtv3Rn7W3mgPxhU9K/ScQsAP7hUibX39j7fakFPskvXusvfa0b4Q" crossorigin="anonymous"></script>
    <script src="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/js/bootstrap.min.js" integrity="sha384-JZR6Spejh4U02d8jOt6vLEHfe/JQGiRRSQQxSfFWpi1MquVdAyjUar5+76PVCmYl" crossorigin="anonymous"></script>
  </body>
</html>