<!doctype html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport"
          content="width=device-width, user-scalable=no, initial-scale=1.0, maximum-scale=1.0, minimum-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <title>empleado</title>
</head>
<body>
            <?php


            $dni = $_GET['dni'];
            if(isset($_GET['dni'])){
                include ("conexion.php");

                $resultado=mysqli_query($conexion,"select * from empleados where dni = '$dni'");
                $row = mysqli_fetch_array($resultado);


            }


            ?>


           <table>
                <tr>
                    <p><strong>ID: </strong><?php echo $row['id']; ?></p>
                    <p><strong>nombre: </strong><?php echo $row['nombre'];?></p>
                    <p><strong>apellido: </strong><?php echo $row['apellido']; ?></p>
                    <p><strong>dni: </strong><?php echo $row['dni']; ?></p>
                    <br/>
                </tr>
           </table>
            <a href="empleados.php">Inicio</a>


</body>
</html>
