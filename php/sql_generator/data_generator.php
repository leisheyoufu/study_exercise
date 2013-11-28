<?php
/** * 
 * User: Chenglong
 * Date: 13-11-14
 * Time: 上午11:03
 */


define('DEST_SERVER', '127.0.0.1');
define('DEST_USER', 'root');
define('DEST_DB_PASSWORD', '');
define('DEST_DB', 'ht_');
define('PER_NUMBER',1024);


ini_set("memory_limit","512M");
ini_set('max_execution_time', 0);
chdir('../../');
require_once('/classes/db/adodb5/adodb.inc.php');
$curr_dir = getcwd();


class Db_Import
{
    protected  $start;
    const LOG_FILE = 'import.log';
    public function __construct($start = 0)
    {
        $this->start = $start;
    }
    protected function createConnection($db_server, $db_username, $db_password, $db_database){
        $db = ADONewConnection ( 'mysqli' );
        if (!$db->Connect ( $db_server, $db_username, $db_password, $db_database )) {
            exit();
        }
        return $db;
    }

    protected  function  batchInsertSql($table, $data, $parameters = '')
    {
        $first_data = $data[0];
        $query = 'INSERT INTO ' . $table . ' (';
        while (list($columns,) = each($first_data)) {
            $query.= $columns . ', ';
        }
        $query = substr($query, 0, -2) . ') VALUES (';

        foreach($data as $d)
        {
            while (list(, $value) = each($d)) {
                switch ((string)$value) {
                    case date('Y-m-d H:i:s') :
                        $query.= "'" . date('Y-m-d H:i:s') . "', ";
                        break;
                    case 'null':
                        $query.= 'null, ';
                        break;
                    default:
                        $query.= '\'' . addslashes($value) . '\', ';
                        break;
                }
            }
            $query = substr($query, 0, -2) . '),(';
        }
        $query = substr($query, 0, -2).';';
        return $query;
    }
    public function getStart()
    {
        return $this->start;
    }
    public function setStart($start=0)
    {
        $this->start = $start;
    }
}

class Db_Generator extends Db_Import
{
    const LOG_KEY = '[Generator]';
    private $d_db;
    public function __construct($start = 0)
    {
        parent::__construct($start);
        self::init();
    }
    private function init()
    {
        if (isset ( $this->d_db ) && $this->d_db instanceof ADOConnection) {
            return $this->d_db;
        }
        $db_server = DEST_SERVER;
        $db_username =  DEST_USER;
        $db_password = DEST_DB_PASSWORD;
        $db_database = DEST_DB;
        $this->d_db = $this->createConnection($db_server, $db_username, $db_password, $db_database);
        return $this->d_db;
    }
    public function generator()
    {
        $sql_array = array();
        for($i = $this->start;$i<$this->start+ PER_NUMBER;$i++)
        {
            $sql_data['mid'] = $i;
            $sql_data['cid'] = $i;
            $sql_data['r'] = $i*1000;
            $sql_data['money'] = 5;
            $sql_data['value'] = 1.7;
            $sql_array[] = $sql_data;
        }
        return $sql_array;
    }
    public function batchInsert($table)
    {
        $sql_array = self::generator();
        $sql = self::batchInsertSql($table,$sql_array);
        $result = $this->d_db->Execute($sql);
        return $result;
    }
}



class runtime
{
    var $StartTime = 0;
    var $StopTime = 0;

    function get_microtime()
    {
        list($usec, $sec) = explode(' ', microtime());
        return ((float)$usec + (float)$sec);
    }

    function start()
    {
        $this->StartTime = $this->get_microtime();
    }

    function stop()
    {
        $this->StopTime = $this->get_microtime();
    }

    function spent()
    {
        return round(($this->StopTime - $this->StartTime) * 1000, 1);
    }

}

function job()
{
    $start = 0;
    $d_dao = new Db_Generator($start);
    while($start < 1000000)
    {
        $d_dao->batchInsert("test_table");
        $start+=PER_NUMBER;
        $d_dao->setStart($start);
    }
}
print "job start";
$runtime= new runtime;
$runtime->start();

job();

$runtime->stop();
echo "<br/>spend ".$runtime->spent()." ms <br/>";