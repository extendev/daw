<?php

/**
 * This file is part of the Daw package.
 *
 * (c) Axel Tessier <axel.tessier@extendev.net>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace Daw\Core\Connector\Ssh;

/**
 * SSH Connector Class
 *
 * This connector allows access to any hosts using SSH,
 * providing that host has an SSHd server running
 *
 * The class implements methods to connect to a remote SSHd server,
 * execute commands and disconnect.
 *
 * The remote host connection is opened upon successful call to connect()
 * and remains opened till disconnect() is called.
 *
 * This connectors requires the libssh2 to be enabled in PHP. See
 * http://www.php.net/manual/intro.ssh2.php for more details
 *
 * @package Modules\Core
 * @subpackage Connector
 * @link http://www.php.net/manual/intro.ssh2.php
 * @author Axel Tessier <axel.tessier@extendev.net>
 * @version $Id$
 */
class SshConnector implements Daw\Core\Connector\Connector {

    /**
     * Options to connect to the SSH server
     *
     * List of available options:
     *  - host: host to connect to
     *  - username
     *  - password
     *  - publickey
     *  - privatekey
     *  - passphrase
     *
     * @var array $options options used to connect to the SSHd server
     * @link
     */
    protected $options = array();

    /**
     * Currently opened connection instance
     * Being set through connect() call and remove by calling disconnect().
     * All commands sent via exec() will be executed on this instance.
     * @var object connection opened by connect() call
     */
    protected $connection = null;


    /**
     * Create a new connector with specified options
     *
     * @param array[string => string] $options default options to use
     */
    public function __construct($options = array()) {
        $this->options = $options;
    }

    /**
     * Get option currently set
     *
     * If option is not set, the function will return $default value
     *
     * @param string $name option name
     * @param string $default value to return if option is not set
     * @return string option value
     */
    public function getOption($name, $default = null) {
        if (!isset($this->options[$name])) {
            return $default;
        }

        return $this->options[$name];
    }

    /**
     * Establish connection to a remote SSH server
     *
     * The options passed to this method override any options defined when calling constructor.
     *
     * @throws \Exception if connection could not be established
     * @param string $host host to connect to. If not set, uses the 'host' option if set.
     * @param array[string => string] $options connection options to use
     */
    public function connect($host = null, $options = array()) {
        $this->options = array_merge($this->options, $options);

        if ($host === null) {
            $host = $this->getOption('host');
        }

        if (!($this->connection = ssh2_connect($host, $this->getOption('port', 22)))) {
            throw new \Exception('Cannot connect to server');
        }

        switch ($this->getOption('authentication')) {
            case 'password':
                if (!ssh2_auth_password($this->connection,
                    $this->getOption('username'),
                    $this->getOption('password'))) {
                    throw new \Exception('Credentials rejected by server');
                }
                break;
            case 'pubkey':
                if (!ssh2_auth_pubkey_file($this->connection,
                        $this->getOption('username'),
                        $this->getOption('publicKey'),
                        $this->getOption('privateKey'),
                        $this->getOption('passphrase'))) {
                    throw new \Exception('Authentication rejected by server');
                }
                break;
            case 'hosts':
                break;
        }
    }

    /**
     * Run a command on the remote host
     *
     * @param string $cmd command to execute
     * @return string output of the command
     */
    public function exec($cmd) {
        if (!($stream = ssh2_exec($this->connection, $cmd))) {
            throw new \Exception('SSH command failed');
        }
        stream_set_blocking($stream, true);
        $data = "";
        while ($buf = fread($stream, 4096)) {
            $data .= $buf;
        }
        fclose($stream);
        return $data;

        /*
         *
        $stream = ssh2_exec($conn, '/0xDATA/apps/php-5/bin/php -v');
        $errorStream = ssh2_fetch_stream($stream, SSH2_STREAM_STDERR);

        // Enable blocking for both streams
        stream_set_blocking($errorStream, true);
        stream_set_blocking($stream, true);

        // Whichever of the two below commands is listed first will receive its appropriate output.  The second command receives nothing
        echo "Output: " . stream_get_contents($stream);
        echo "Error: " . stream_get_contents($errorStream);

        // Close the streams
        fclose($errorStream);
        fclose($stream);
         *
         */
    }

    /**
     * Disconnect to the remote host
     */
    public function disconnect() {
        if ($this->connection !== null) {
            $this->exec('exit;');
        }

        $this->connection = null;
    }

    /**
     * Destructor
     * Ensure disconnect() is called if a connection is still opened
     */
    public function __destruct() {
        $this->disconnect();
    }
}
