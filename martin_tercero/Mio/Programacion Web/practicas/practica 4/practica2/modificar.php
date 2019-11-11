<!doctype html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport"
          content="width=device-width, user-scalable=no, initial-scale=1.0, maximum-scale=1.0, minimum-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <title>Modificar empleado</title>
</head>
<body>

<div align="center">

    <h3>Modificar empleado</h3>

    <?php
    session_start();



    if(!isset($_SESSION["u_usuario"])){

        header("location:login.php");

    }
    $dni=$_REQUEST['dni'];

    include ("conexion.php");
    /*if($_POST['cancelar']){
        header("location: empleados.php");
    }*/

    $query="Select * from empleados where dni='$dni'";
    $resultado = $conexion->query($query);
    $row=$resultado->fetch_assoc();
    ?>

    <form action="modificar_empleado.php" method="post">


        <br/>
        <input type="text" required name="id" placeholder="id..." value="<?php echo $row['id']; ?>" /><br/><br/>
        <input type="text" required name="nombre" placeholder="Nombre..." value="<?php echo $row['nombre']; ?>" /><br/><br/>
        <input type="text" required name="apellido" placeholder="apellido..." value="<?php echo $row['apellido']; ?>" /><br/><br/>
        <input type="text" required name="dni" placeholder="dni..." value="<?php echo $row['dni']; ?>" /><br/><br/>
        <input type="hidden" name="antiguo" value="<?php echo $row["dni"];?> "/>
        <input type="submit" name="modificar" value="Aceptar">    <input type="submit" name="cancelar" value="Cancelar">

    </form>
</div>
</body>
</html>
