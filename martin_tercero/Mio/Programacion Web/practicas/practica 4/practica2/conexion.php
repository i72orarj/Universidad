<?php
/**
 * Created by PhpStorm.
 * User: paez
 * Date: 24/10/17
 * Time: 20:03
 */
/*class empleadosQueary{

    public $dbc;

    public  function __construct(){
        $this->dbc = $this->dbconnect();
    }

    public function dbconnect(){
            $dbc = null;
        try{
            $dbc = new mysqli('localhost', 'root', 'root', 'empresa');
        }catch(mysqli_sql_exception $exception){
            return null;
        }
        return $dbc;

    }

}*/

/*try {
    $db = new PDO('mysql:host=localhost;dbname=empresa', 'paez', 'root');
} catch (PDOException $e) {
    print "¡Error!: " . $e->getMessage() . "<br/>";
    die();
}*/



$conexion = new mysqli('localhost','paez','root','empresa');

if($conexion->connect_error){
    echo "No se ha podido acceder a la base de datos";
    exit();
}



?>