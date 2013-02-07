<?php

/*
 * This file is part of the Daw package.
 *
 * (c) Axel Tessier <axel.tessier@extendev.net>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace Daw\Core\Module;

/**
 * Application Module base class
 *
 * @package Daw
 * @subpackage Module
 * @author Axel Tessier <axel.tessier@extendev.net>
 * @version $Id: Event.inc 112 2003-08-22 06:22:40Z  $
 */
class Module {

    /**
     * @var string $name module name
     */
    protected $name = null;

    /**
     *
     */
    protected $core = null;

    /**
     *
     */
    protected $info = null;

    /**
     *
     */
    protected $config = null;


    /**
     * Module constructor
     *
     * This constructor does not call load() method.
     * It is up to the parent that instanciated the object to trigger module loading.
     *
     * @param Core $core
     */
    public function __construct($core, $name) {
        $this->core = $core;
        $this->name = $name;
    }

    /**
     * Return module name
     *
     * @return string
     */
    public function getName() {
        return $this->name;
    }

    /**
     * Return core current instant
     *
     * @return \Daw\Core\Core
     */
    public function core() {
        return $this->core;
    }

    /**
     * Return module information
     *
     * @return object
     */
    public function info($value = null) {
        if ($value === null) {
            return $this->info;
        }

        if (!isset($this->info[$value])) {
            return false;
        }

        return $this->info[$value];
    }

    /**
     * Return installation path of the module base directory or child
     */
    protected function getPath($file) {
        return $this->core()->basePath . '/Modules/' . $this->getName() . '/' . $file;
    }

    /**
    * Load module into memory
    *
    * @see Daw\Core\Module.Module::load()
    */
    public function load() {
        $moduleInfoPath = $this->getPath('module.info');

        $contents = file_get_contents($moduleInfoPath);
        $this->info = $this->core->yaml->parse($contents);
        //print_r($this->info);
        $this->core()->log->debug("    => (" . __NAMESPACE__ . ") Module info loaded: " . strlen($contents) . " bytes.\n");
    }

    /**
     * Return configuration of the module
     */
    public function config($name = null, $default = false) {
        if ($name == null) {
            return $this->config;
        }

        return isset($this->config[$name]) ? $this->config[$name] : $default;
    }

    /**
     * Load module configuration
     *
     * @param array $config
     */
    public function loadConfig($config = array()) {
        //echo("    => (" . __NAMESPACE__ . ") Module " . $this->getName() . " config loaded: " . print_r($config, true) . ".\n");
        $this->config = $config;
    }

    /**
     * Unload module data
     *
     * @see Daw\Core\Module.Module::unload()
     */
    public function unload() {
        $this->config = null;
    }

    /**
    * Return list of operations for this module
    *
    * @see Daw\Core\Module.Module::operationList()
    */
    public function operationList($objectName = null) {
        $operationList = array();
        foreach ($this->info('operations') as $operationName => $operationInfo) {
            $operationList[] = new \Daw\Core\Object\Operation($operationName, $operationInfo);
        }

        return $operationList;
    }

    /**
     * Get operation information
     *
     * @see Daw\Core\Module.Module::operationInfo()
     */
    public function operationInfo($objectName, $operationName) {

        $objectName = $objectName ? $objectName : $this->getName();
        foreach ($this->info('operations') as $op => $operation) {
            $object = isset($operation['object']) ? $operation['object'] : $this->getName();
            $name = isset($operation['operation']) ? $operation['operation'] : $op;
            if ($objectName == $object && $operationName == $name) {
                return $operation;
            }
        }

        return false;
    }

    public function call($object, $operationName, $args = array()) {
        $operationNS = 'Daw\\Modules\\' . $this->getName() . '\\Operations\\' . ucwords($object) . ucwords($operationName);
        $operation = new $operationNS($this, $this->operationInfo($object, $operationName));

        return $operation->call($args);
    }

    /**
    * Return true if is provides requested feature
    *
    * @param unknown_type $feature
    */
    public function isProviderFor($feature) {
        foreach ($this->info['provides'] as $featureProvided) {
            if ($featureProvided == $feature) {
                return true;
            }
        }

        return false;
    }

    /**
     * Return provider for specific feature
     *
     * @param string $feature
     */
    public function getProviders() {
        return isset($this->info['provides']) ? $this->info['provides'] : array();
    }

    /**
     * Return provider for specific feature
     *
     * @param string $feature
     */
    public function getProvider($feature) {
        if (!$this->isProviderFor($feature)) {
            return null;
        }

        $providerClass = 'Daw\\Modules\\' . $this->getName() . '\\Providers\\' . ucwords($feature) . 'Provider';
        $provider =  new $providerClass($this->core, $this);

        return $provider;
    }


    public function isHandlerFor($object, $operationName) {
        return true;
    }
}


