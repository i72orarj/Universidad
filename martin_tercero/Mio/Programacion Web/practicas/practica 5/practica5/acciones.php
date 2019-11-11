<?php
session_start();

include ("conexion.php");


try{

    $tdb=new PDO("mysql:host=localhost; dbname=empresa","paez","root");

    $tdb->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

    $tdb->beginTransaction();


    if(isset($_POST['aceptar'])){
       $pdo=$tdb->prepare("update empleados set ");

       $pdo = executed();

       $tdb->commit();


    }


    if(isset($_POST['rechazar'])){

        $pdo=$tdb->prepare("delete from peticiones where");

        $pdo = executed();

        $tdb->commit();
    }



}catch (exception $e){
    $tdb->rollBack();
    die("no se pudo enviar la peticion" . $e->getMessage());


}