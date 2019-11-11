<?php
include("conexion.php");
?>

<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
<title>ABC</title>
</head>
<script>
function CargarVideos(){
	window.open("https://www.youtube.com/watch?v=HcLd7Cyjuw8");
	window.open("https://www.youtube.com/watch?v=Z0YRvzNNYNk");
	}
</script>
<body onLoad="CargarVideos();">
<?php

            //Generales
			$Id=$_POST["Emp"];
			$ApeP=$_POST["APa"];;
			$ApeM=$_POST["AMa"];
			$Nom=$_POST["Nom"];
			$Sex=$_POST["Sex"];
			$Fec=$_POST["Fec"];
			$Dom=$_POST["Dom"];
			$Ciu=$_POST["Ciu"];
			$CP=$_POST["CP"];
			$Est=$_POST["Est"];
			//Escolaridad
			$Nivel=$_POST['Escu'];
		    $Titulo=$_POST['Titu'];
			//Experiencia
			$NomEmp=$_POST['NomE'];
			$Puesto=$_POST['Puest'];
			$GiroE=$_POST['GEmp'];
			$Dire=$_POST['DirE'];
			$Sueldo=$_POST['Suel'];
			$TiemTra=$_POST['TieT'];
			//Alta
			$PuestoAsi=$_POST['PA'];
			$Dpto=$_POST['DE'];
			$SueldoAlt=$_POST['SU'];
			$JornadaTr=$_POST['SUL'];
			$HorasTra=$_POST['HT'];
			$JornadTra=$_POST['JT'];
			
 if(isset($_POST["boton"])){
     $VBoton=$_POST["boton"];
	 $bus=$_POST["Emp"];
	 
  if($VBoton=="Buscar"){
		$sql="select * from empleado where NumEmplado='$bus'";
		$cs=mysql_query($sql,$Con);
		while($resul=mysql_fetch_array($cs)){
			$varId=$resul[0];
			$varApeP=$resul[1];
			$varApeM=$resul[2];
			$varNom=$resul[3];
			$varSex=$resul[4];
			$varFec=$resul[5];
			$varDom=$resul[6];
			$varCiu=$resul[7];
			$varCP=$resul[8];
			$varEst=$resul[9];
			
			}
			if($varSex=="Masculino"){
				$varSex="selected";
				}	
			//busqueda Escolaridad	
		   $sql="select * from escolaridad where NumEmpleado='$bus'";
		     $cs=mysql_query($sql,$Con);
		       while($resul=mysql_fetch_array($cs)){
			     $varEsc=$resul[1];
			     $varTit=$resul[2];		
			}	
			// Experiencia Laboral
			   $sql="select * from experiencia where NumEmple='$bus'";
		         $cs=mysql_query($sql,$Con);
		          while($resul=mysql_fetch_array($cs)){
			       $varNoE=$resul[1];
			       $varPuE=$resul[2];	
				   $varGiE=$resul[3];
			       $varDiE=$resul[4];
				   $varSuE=$resul[5];
			       $varAnE=$resul[6];
			     }
		    // Alta Empleado
			   $sql="select * from altaemp where NumEmpleado='$bus'";
		         $cs=mysql_query($sql,$Con);
		          while($resul=mysql_fetch_array($cs)){
			       $varPues=$resul[1];
			       $varDepa=$resul[2];	
				   $varSuel=$resul[3];
			       $varJoSu=$resul[4];
				   $varHoTa=$resul[5];
			       $varJoHo=$resul[6];
			      }
				  if($varJoSu=="Quinsenales"){
				   $varJoSu="selected";
				  }
				  if($varJoHo=="Quinsenales"){
				   $varJoHo="selected";
				  }
		}
		//Guardar
	  if($VBoton=="Guardar"){
			
		$sql="insert into empleado values ('$Id','$APa','$AMa','$Nom','$Sex','$Fec','$Dom','$Ciu','$CP','$Est')";
		$sql1="insert into escolaridad values ('$Id','$Nivel','$Titulo')";
		$sql2="insert into experiencia values ('$Id','$NomEmp','$Puesto','$GiroE','$Dire','$Sueldo','$TiemTra')";
		$sql3="insert into altaemp values ('$Id','$PuestoAsi','$Dpto','$SueldoAlt','$JornadaTr','$HorasTra','$JornadTra')";

		$cs=mysql_query($sql,$Con);
		$cs1=mysql_query($sql1,$Con);
		$cs2=mysql_query($sql2,$Con);
		$cs3=mysql_query($sql3,$Con);
		   echo "<script> alert('Datos Almacenados Correctamente del Empleado');</script>";
		}	
		//Eliminar
	  if($VBoton=="Eliminar"){
		    $Id=$_POST["Emp"];	
			
		$sql="delete from empleado where NumEmplado='$Id'";
		$sql1="delete from escolaridad where NumEmpleado='$Id'";
		$sql2="delete from experiencia where NumEmple='$Id'";
		$sql3="delete from altaemp where NumEmpleado='$Id'";
				
		$cs=mysql_query($sql,$Con);
		$cs1=mysql_query($sql1,$Con);
		$cs2=mysql_query($sql2,$Con);
		$cs3=mysql_query($sql3,$Con);
		echo "<script> alert('Se Elimnino Correctamente al Empleado de Clave '+ $Id);</script>";
		}
		//Actualizar
	   if($VBoton=="Actualizar"){
		    		
		$sql="update empleado set ApePaterno='$ApeP',ApeMaterno='$ApeM',Nombre='$Nom',Sexo='$Sex',FeNac='$Fec',Domicilio='$Dom',Ciudad='$Ciu',CP='$CP',Estado='$Est' where NumEmplado='$Id'";
		$sql1="update escolaridad set Nivel='$Nivel',Titulo='$Titulo' where NumEmpleado='$Id'";
		$sql2="update experiencia set NomEmpresa='$NomEmp',Puesto='$Puesto',GiroE='$GiroE',DirE='$Dire' ,Sueldo='$Sueldo,Antiguedad='$TiemTra' where NumEmple='$Id'";
		$sql3="update altaemp set Puesto='$PuestoAsi',Departamento='$Dpto',Sueldo='$SueldoAlt',JornadaSueldo='$JornadaTr' ,HoraT='$HorasTra',JornadaHora='$JornadTra' where NumEmpleadoado='$Id'";
		
		$cs=mysql_query($sql,$Con);
		$cs1=mysql_query($sql1,$Con);
		$cs2=mysql_query($sql2,$Con);
		$cs3=mysql_query($sql3,$Con);
		echo "<script> alert('Se actualizo correctamente');</script>";
		}
		
    }

?>
 <form  name="formulario" method="post" action="">
<p>Datos Generales.-</p>
<p>Numero de Empleado: 
  <input type="text" name="Emp" value="<?php echo $varId?>" />
  <td><input type="submit" name="boton"  value="Buscar"  /></td>
</p>
<p>Apellido paterno: 
  
  <input type="text" name="APa" value="<?php echo $varApeP?>" />
</p>
<p>Apellido materno: 
  <input type="text" name="AMa" value="<?php echo $varApeM?>" />
</p>
<p>Nombre(s): 
  <input type="text" name="Nom" value="<?php echo $varNom?>" />
</p>
<p>Sexo:
  <select name="Sex">
  <option>Femenino</option>
  <option <?php echo $varSex?> >Masculino</option>
</select>
</p>
<p>Fecha De Nacimiento: <input type="text" name="Fec" value="<?php echo $varFec?>" /></p>
 
<p>Domicilio: 
  <input type="text" name="Dom" value="<?php echo $varDom?>" />
</p>
<p>Ciudad: 
  <input type="text" name="Ciu" value="<?php echo $varCiu?>" />
</p>
<p>C.P. 
  <input type="text" name="CP" value="<?php echo $varCP?>" />
</p>
<p>Estado: 
  <input type="text" name="Est" value="<?php echo $varEst?>" />
</p>


<p>&nbsp;</p>
<p>Escolaridad.- </p>
<p>Nivel Maximo de Estudios (Certificado o Titulo)
  <label><br />
    <input type="radio" name="Escu" value="Pri" id="RadioGroup2_0" />
  Primaria</label>
  <br />
  <label>
    <input type="radio" name="Escu" value="sec" id="RadioGroup2_1" />
    Secundaria</label>
  <br />
  <label>
    <input type="radio" name="Escu" value="pre" id="RadioGroup2_2" />
    Preparatoria</label>
  <br />
  <label>
    <input type="radio" name="Escu" value="uni" id="RadioGroup2_3" />
    Universidad</label>
  <br />
  <label>
    <input type="radio" name="Escu" value="post" id="RadioGroup2_4" />
    Post Grado</label>
</p>
<p>Titulo Obtenido: 
  <input type="text" name="Titu" value="<?php echo $varTit?>" />
</p>
<p>&nbsp;</p>
<p>Experiencia Laboral.-</p>
<p>Empleo Anterior: </p>
<p>Nombre de la Empresa: 
  <input type="text" name="NomE" value="<?php echo $varNoE?>" />
Puesto: 
<label for="Puest"></label>
<input type="text" name="Puest" value="<?php echo $varPuE?>" />
Giro de la Empresa: 
<input type="text" name="GEmp" value="<?php echo $varGiE?>" />
</p>
<p>Direccion de la Empresa: 
  <input type="text" name="DirE" value="<?php echo $varDiE?>" />
Sueldo: 
<input type="text" name="Suel" value="<?php echo $varSuE?>" /> 
Tiempo que Trabajo:
<input type="text" name="TieT" value="<?php echo $varAnE?>" />
Años.</p>
<p>&nbsp;</p>
<p>Alta del Empleado.-</p>
<p>Puesto asignado:
  <input type="text" name="PA" value="<?php echo $varPues?>" />
Departamento: 
<input type="text" name="DE" value="<?php echo $varDepa?>" />
Sueldo: 
<input type="text" name="SU" value="<?php echo $varSuel?>" />
Pesos
<select name="SUL" >
<option >Semanales</option>
<option <?php echo $varJoSu?> >Quinsenales</option>
</select>
</p>
<p>Horas a Trabajar: 
  <input type="text" name="HT" value="<?php echo $varHoTa?>"  />
  <select name="JT">
  <option >Semanales</option>
  <option <?php echo $varJoHo?>>Quinsenales</option>
  </select>
</p>
<input type="submit" name="boton" value="Guardar" /> <input type="submit" name="boton" value="Eliminar" /> <input type="submit" name="boton" value="Actualizar" />
</form>
<form method="post" action ="empleados.php">
    <input type="text" name="name">
    <input type="text" name="apellido">
    <input type="submit"value="imprimir">

</form>

<?php

$name = $_POST['name'];
$apellido = $_POST['apellido'];

echo '<p>' .$name .'</p>';
echo '<p>' .$apellido .'</p>';

$consulta = "select * from empleados";
$resultado = mysqli_fetch_row($conexion,$consulta);
while($fila = mysqli_fetch_row($resultado)){
    echo $fila[0] . " ";
    echo $fila[1] . " ";
    echo $fila[2] . " ";
    echo $fila[3] . " ";
    echo "<br>";

}




?>
</body>
</html>
<?php
$busqueda = $_GET['nombre'];
include ("conexion.php");


$query ="Select * from empleados where nombre='$busqueda'";

$resultado = $conexion->query($query);
$row=$resultado->fetch_assoc();


?>
<tr>
    <p><strong>ID: </strong><?php echo $row['id']; ?></p>
    <p><strong>nombre: </strong><?php echo $row['nombre'];?></p>
    <p><strong>apellido: </strong><?php echo $row['apellido']; ?></p>
    <p><strong>dni: </strong><?php echo $row['dni']; ?></p>
    <br/>
</tr>

<a href="empleados.php">Inicio</a>


<?php
$nombre = $_POST['nombre'];
$query = $db->prepare("SELECT * FROM empleados WHERE nombre = :nombre");
$query->bindParam(':nombre', $nombre);
$query->execute();
?>

<?php foreach ($query as $row): ?>
    <p><strong>ID: </strong><?php echo $row["id"];?></p>
    <p><strong>nombre: </strong><?php echo $row["nombre"];?></p>
    <p><strong>apellido: </strong><?php echo $row["apellido"];?></p>
    <p><strong>dni: </strong><?php echo $row["dni"];?></p>
<?php endforeach ?>
<br/>

<a href="empleados.php">Inicio</a>
