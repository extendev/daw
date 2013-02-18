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
     * @var Core daw instance
     */
    protected $core = null;

    /**
     * @var string module information as collected from Module's module.info file
     */
    protected $info = null;

    /**
     * @var array module configuration settings as specified in module .yml file
     */
    protected $config = null;


    /**
     * Module constructor
     *
     * This constructor does not call load() method.
     * It is up to the parent that instanciated the object to trigger module loading.
     *
     * @param Core $core daw instance
     * @param string $name name of the module
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
     * Return module information or FALSE if not set
     *
     * @param object $value label/key of the module information to return
     * @return object the module information if defined, FALSE otherwise
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
     * Return absoluate path of a file included in module, or
     * module installation path if no file has been specified
     *
     * @param string $file relative path of the file
     * @return string absolute path of the file
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
     * Return configuration setting of the module, FALSE if not set
     *
     * @param string $name name of the configuration setting to find
     * @param object $default value to return if the configuration setting is not set
     * @return object configuration setting value or FALSE if not set and no default value has been specified
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
     * @param string $objectName name of the object
    */
    public function operationListBasic($objectName = null) {
      return $this->info('operations');
    }

    /**
     * Return list of operations for this module and for a specfic object
     *
     * @param string $objectName name of the object
     * @return array list of Operation instances available for the object
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
     * Get operation information for this module and for a specfic object, FALSE otherwise
     *
     * @param string $objectName name of the object
     * @param string $operationName name of the operation
     * @return array information associated to the operation as available in Module's module.info file
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

    /**
     * Call module operation
     *
     * @param string $object name of the object the operation is associated to. May be null for module global operation
     * @param string $operationName name of the operation to call
     * @param array arguments to pass to the operation
     * @return object response returned by the operation if completed successfully
     */
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
     * Return list of all providers published by the module
     *
     * @return array key/value pair list of proviers, where key is the feature provider, and name the actual provider class name
     */
    public function getProviders() {
        return isset($this->info['provides']) ? $this->info['provides'] : array();
    }

    /**
     * Return provider for specific feature, or NULL if none available for this module
     *
     * @param string feature requested
     * @return Provider the provider instance published by the module
     */
    public function getProvider($feature) {
        if (!$this->isProviderFor($feature)) {
            return null;
        }

        $providerClass = 'Daw\\Modules\\' . $this->getName() . '\\Providers\\' . ucwords($feature) . 'Provider';
        $provider =  new $providerClass($this->core, $this);

        return $provider;
    }

    /**
     * Return TRUE if module has an operation with given name of for the specified $object, false otherwise
     *
     * @param string $object name of the object
     * @param string $operationName name of the operation
     * @return boolean
     */
    public function isHandlerFor($object, $operationName) {
        return true;
    }
}


