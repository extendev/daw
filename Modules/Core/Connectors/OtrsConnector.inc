<?php

/**
 * This file is part of the Daw package.
 *
 * (c) Axel Tessier <axel.tessier@extendev.net>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace Daw\Modules\Core\Connectors;

use \Daw\Core\Connector\Connector;


/**
 * Application Connector - OTRS
 *
 * Access to OTRS Web services using HTTP::SOAP transport defined in OTRS
 *
 * This connectors requires the libssh2 to be enabled in PHP. See
 * http://www.php.net/manual/intro.ssh2.php for more details
 *
 * @package Core
 * @subpackage Connectors
 * @link http://www.php.net/manual/intro.ssh2.php
 * @author Axel Tessier <axel.tessier@extendev.net>
 * @version $Id$
 */
class OtrsConnector implements Connector {

    /**
     * Options to connect to the OTRS service
     *
     * List of available options:
     *  - location
     *  - login
     *  - password
     *
     * @var array $options options used to connect to the SSHd server
     */
    protected $options = array();


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
     * Set credentials used to connect to OTRS service
     *
     * @param string $login
     * @param string $password
     */
    public function setAuthentication($login, $password) {
        $this->options['login'] = $login;
        $this->options['password'] = $password;
    }

    /**
     * Call any OTRS public API
     *
     * @param array[string => string] $params call parameters
     * @return string call response instance
     */
    protected function call($params) {
        $client = new \SoapClient(null, array(
            'location'  => $this->getOption('location'),
            'uri'       => "Core",
            'trace'     => 1,
            'login'     => $this->getOption('login'),
            'password'  => $this->getOption('password'),
            'style'     => SOAP_RPC,
            'use'       => SOAP_ENCODED
        ));

        $callParams = array_merge(
            array(
                $this->getOption('login'), $this->getOption('password')
            ),
            $params
        );

        $result = $client->__soapCall("Dispatch", $callParams);

        return $result;
    }

    public function Authenticate($login, $password) {
        return $this->call(array(
            "AuthObject", "Auth",
            "User", $login,
            "Pw", $password
        ));
    }

    /**
     * OTRS - Get Ticket information
     *
     * @param long $ticketId
     * @return string TicketGet instance
     */
    public function TicketGet($ticketId) {
        return $this->call(array(
            "TicketObject", "TicketGet",
            "TicketID", $ticketId
        ));
    }

    /**
     * OTRS - Create new ticket and return its ID
     *
     * @return string TicketCreateNumber instance
     */
    public function TicketCreateNumber() {
        return $this->call(array(
                "TicketObject", "TicketCreateNumber"
        ));
    }

    /**
     * OTRS - Search for existing ticket using its ID
     *
     * @param long $ticketId
     * @return string TicketNumberLookup instance
     */
    public function TicketNumberLookup($ticketId) {
        return $this->call(array(
            "TicketObject", "TicketNumberLookup",
            "TicketID", $ticketId
        ));
    }

}
