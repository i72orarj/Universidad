<?php

include ("conexion.php");


$dni = $_REQUEST['dni'];

if(isset($_POST['eliminar'])){
    $query = "delete from empleados where dni='$dni' ";
    $resultado = $conexion->query($query);
    header("location: empleados.php");
}else{
    echo "No se han eliminado los datos";
}

if(isset($_POST['cancelar'])){
    header("location: empleados.php");
}
/*
if(isset($_POST['eliminar'])) {

    if (strnatcasemp($_POST['cancelar'], "Cancelar") == 0) {
        header("location: empleados.php");
    }
    else {
        $query = "delete from empleados where dni='$dni' ";
        $resultado = $conexion->query($query);
        header("location: empleados.php");

    }
}*/

/*
$query = "delete from empleados where dni='$dni' ";
$resultado = $conexion->query($query);
if($resultado){
    header("location: empleados.php");
}else{
    echo "No se han eliminado los datos";
}*/
?>
