<?php  
	//buatlah koneksi ke database dbminiolt
		$konek = mysqli_connect("localhost", "id17573185_root", "Amqe1234567*", "id17573185_dbminiolt");

	//baca data dari tabel tb_miniolt
	$sql = mysqli_query($konek, "select * from tb_miniolt order by id desc"); //data terakhir akan berada diatas

	//baca data paling atas
	$data = mysqli_fetch_array($sql);
	$kalianak = $data['kalianak'];

	//uji, apabila status tandes belum ada maka anggap nilai awal aman
	if( $kalianak != "vandalisme" ) $kalianak = "aman";

	//cetak status tandes
	echo $kalianak;

?>