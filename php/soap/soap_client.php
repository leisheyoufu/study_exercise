<?php
$opts = array('location' => 'http://localhost/test/cltest/soap/soap_serv.php',
					'uri'=>'urn:pc_SOAP_return_time');
$client = new SOAPClient(null,$opts);
$result = $client->__soapCall('return_time',array());
print "The local time is $result.\n";


$author = $client->__soapCall('return_author',array('group'=>true));  // group 名字无所谓
print "The author is $author. \n";

$set_length = new SOAPVar(12,XSD_INT);
$length_header = new SOAPHeader('urn:pc_SOAP_return_time','set_length',$set_length);

$result = $client->__soapCall('fault',array(7),array(),array($length_header));
print "fault length is $result. \n";


?>