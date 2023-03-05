<?php
	//koneksi ke database
	$konek = mysqli_connect("localhost", "id17573185_root", "Amqe1234567*", "id17573185_dbminiolt");

	//baca data yang dikirim dari esp32
	$tandes = $_GET['tandes'];
	$kapasan = $_GET['kapasan'];
	$kalianak = $_GET['kalianak'];

	//simpan ke tabel tb_miniolt

	//auto increment = 1 apabila ID dikosongkan
	mysqli_query($konek, "ALTER TABLE tb_miniolt AUTO_INCREMENT=1");

	//simpan data sensor ke tabel tb_sensor
	$simpan = mysqli_query($konek, "insert into tb_miniolt(tandes, kapasan, kalianak)values('$tandes', '$kapasan', '$kalianak')");

	//uji simpan utk memberikan respon
	if($simpan)
		echo "Berhasil dikirim";
	else
		echo "Gagal terkirim";

?>