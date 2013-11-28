<?php
class pc_SOAP_return_time
{
	public function return_time()
	{
		return date('Ymd\This');
	}
	
	public function return_author($group)
	{
		if($group)
		{
			return "RedX";
		}		
		return "chenglong";
	}
	
	public function fault($length)
	{
//		if($length < 7)
//		{
//			throw new SOAPFault(1,"len < 7");
//		}
		return $length;
	}
	
	
}
$server = new SOAPServer(null,array('uri'=>'urn:pc_SOAP_return_time'));
$server->setClass('pc_SOAP_return_time');
$server->handle();