<?php
/**
 * Created by PhpStorm.
 * User: paez
 * Date: 22/11/17
 * Time: 18:50
 */
session_start();

try{

    $base=new PDO("mysql:host=localhost; dbname=empresa","paez","root");

    $base->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

    $sql="Select * from usuarios where usuario= :usuario AND  password= :password" ;
    //$sql="Select * from usuarios where usuario= :usuario" ;

    $resultado = $base->prepare($sql);

    $usuario=htmlentities(addslashes($_POST["usuario"]));

    $password=htmlentities(addslashes($_POST["password"]));

    $resultado->bindValue(":usuario",$usuario);

    $resultado->bindValue(":password",hash('ripemd128',$password));



    $resultado->execute();

    $registro=$resultado->rowCount(); // devuelve 0 o 1 y se guarda en la variable

    //while($row=mysqli_fetch_array($sql)){
       // $admin=$row["admin"];
        if($registro!=0){
            $_SESSION['u_usuario'] = $usuario;
            $_SESSION['privilegio'] = $admin;
            //if($_SESSION['privilegio']=='1'){
             //   header("location: admin.php");
           // }

            header("location:empleados.php");

        }else{

            header("location: login.php");


        }




}catch (Exception $e){
    die("Error: " . $e->getMessage());
}

    /*
    $usuario=$_POST["usuario"];
    $password=$_POST["password"];

    include("conexion.php");

    $resultado=$conexion->query("select * from usuarios where usuario='$usuario' and password='$password' ");


    if($resultado = mysqli_fetch_array($resultado)){
        $_SESSION['u_usuario']=$usuario;
        header("location: empleados.php");
    }else{
        header("location: login.php");
    }*/

 ?>