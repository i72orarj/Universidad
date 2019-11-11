<?php

include ("conexion.php");

    $id = $_POST['id'];
    $nombre = $_POST['nombre'];
    $apellido =$_POST['apellido'];
    $dni = $_REQUEST['dni'];
    $sueldo = $_POST['sueldo'];

    $query = "insert into empleados(id,nombre,apellido,dni,sueldo) VALUES('$id','$nombre','$apellido','$dni','$sueldo') ";
    $resultado = $conexion->query($query);
    if($resultado){
        header("location: empleados.php");
    }else{
        echo "No se han guardado los datos";
    }
?>
