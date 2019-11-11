<!doctype html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport"
          content="width=device-width, user-scalable=no, initial-scale=1.0, maximum-scale=1.0, minimum-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <title>Insertar empleado</title>
</head>
<body>
<?php
session_start();



if(!isset($_SESSION["u_usuario"])){

    header("location:login.php");

}
?>
    <div align="center">

        <h3>Añadir un nuevo empleado</h3>
        <form action="guardar.php" method="post">

            <br/>
            <input type="text" name="id" placeholder="id..." value="" /><br/><br/>
            <input type="text" required name="nombre" placeholder="Nombre..." value="" /><br/><br/>
            <input type="text" required name="apellido" placeholder="apellido..." value="" /><br/><br/>
            <input type="text" required name="dni" placeholder="dni..." value="" /><br/><br/>
            <input type="submit" value="Aceptar">

        </form>
    </div>
</body>
</html>
