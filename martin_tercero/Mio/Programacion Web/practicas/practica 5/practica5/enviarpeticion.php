<?php

session_start();
include ("conexion.php");

$id=$_POST['id'];
$dni=$_POST['dni'];
$sueldo=$_POST['sueldo'];

$resultado=mysqli_query($conexion,"select id,dni from empleados");

if($row = mysqli_fetch_array($resultado)){
    $idt=$row["id"];
    $dnit=$row["dni"];

}



try{

    $tdb=new PDO("mysql:host=localhost; dbname=empresa","paez","root");

    $tdb->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

    $tdb->beginTransaction();

    if (($idt==$id) && ($dni==$dnit)){


        $pdo=$tdb->prepare("insert into peticiones(solicitud,peticiones) VALUES (?,?)");

        $pdo->execute(array($dni,$sueldo));

        $tdb->commit();

        header("location:empleados.php");

    }else{
        echo "error al enviar la peticion";

        echo "</br>  <a href='empleados.php'>Inicio</a>";
    }




}catch(Exception $e){

    $tdb->rollBack();

    die("no se pudo enviar la peticion" . $e->getMessage());

}