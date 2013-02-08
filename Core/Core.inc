<?php

/**
 * This file is part of the Daw package.
 *
 * (c) Axel Tessier <axel.tessier@extendev.net>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace Daw\Core;

use \Daw\Core\Provider\NullProvider;
use \Daw\Core\Common\FileUtil;
use \Daw\Core\Formatter\TextIndentFormatter;
use \Daw\Core\Formatter\JsonFormatter;
use \Daw\Core\Formatter\FormatterContext;

/**
 * Bootstrap:
 *  - intialize
 *      - load assigned providers from providers directory
 *      - load modules
 *      - load objects, operations, formatters, providers managed by modules
 *      - load config
 *          * default module
 *          * default operation + args
 *
 *  - launch process
 *      - load args from access point service
 *      - run operation
 *      - format output
 *
 * @author Q.AT
 *
 */
class Core {

    /**
    * Application unique instance
    *
    * @var App
    */
    protected static $_instance = null;

    public $basePath;

    /**
     * Direct object access register
     *
     * Allows object to register to the Core using register() method
     * to be directly accessible from this object
     *
     * Providers are always registered for ease of use
     *
     * @var array
     */
    protected $register = array();

    /**
     * Configuration
     *
     * @var mixed
     */
    protected $config = array();

    /**
     * Service from where call has been initiated
     *
     * @var Service
     */
    protected $service = null;

    /**
     * Service request
     *
     * @var ServiceRequest
     */
    protected $request = null;

    /**
     * Service response
     *
     * @var ServiceResponse
     */
    protected $response = null;


    protected $modules = array();
    protected $providers = array();

    protected $objects = array();
    protected $operations = array();
    protected $formatters = array();


    /**
    * Set/Get singleton instance
    *
    * @return Core
    */
    final public static function instance($instance = null)
    {
        if ($instance !== null) {
            self::$_instance = $instance;
        }

        if (self::$_instance === null) {
            new self();
        }

        return self::$_instance;
    }

    /**
     * Private constructor to ensure singleton
     */
    private function __construct() {
        self::instance($this);

        $this->init();
    }

    /**
     * Register object to be accessed directly from Core using alias specified
     *
     * @param Object $object
     * @param string $name
     */
    public function register($object, $alias) {
        $this->register[$alias] = $object;
        $this->log->debug("  => Registered global alias $alias.");
    }

    /**
     * Magic getter to return object registered with specified alias,
     * NULL if no object could be found
     *
     * @param string $alias
     * @return Object
     */
    final public function __get($alias) {
        if (!isset($this->register[$alias])) {
            return false;
        }

        return $this->register[$alias];
    }

    /*
    * FUNCTIONS
    */
    public function registerFunction($function, $alias) {
        $this->_functions[$alias] = $function;
        $this->log->debug("  => Registered global function $alias.");
    }

    public function __call($method, $args) {
        if (isset($this->_functions[$method])) {
            $function = $this->_functions[$method];
            return call_user_func_array($function, $args);
        } else {
            // That may be a function corresponding to a library of the same name
            //if ($library = $this->$method) {
            //  return call_user_func_array(array($library, $method), $args);
            //} else {
            throw new Exception\Exception('Function not registered to application : ' . $method);
            //}
        }
    }

    /**
     * RUN PROCESS
     */

    protected function loadConfig() {
        $this->log->debug("o Load Config");
        $contents = file_get_contents($this->basePath . '/conf/Daw.yml');
        $this->config = $this->yaml->parse($contents);
        //print_r($this->config);
        $this->log->debug("  + Config loaded: " . strlen($contents) . " bytes.");
    }

    protected function loadModules() {
        $nbModules = 0;
        $this->log->debug("o Load Modules");
        $modules = $this->config['modules'];
        foreach ($modules as $module => $version) {
            $this->log->debug("  - Loading module: " . $module . ", version: " . ($version ? $version : 'any') . "");
            $this->loadModule($module, $version);
            $nbModules++;
        }

        $this->log->debug("  + Modules loaded: " . $nbModules . "");
    }

    public function getModules() {
        return $this->modules;
    }

    public function getModule($name) {
        return isset($this->modules[$name]) ? $this->modules[$name] : false;
    }

    /**
     * Load module with potentially a specific version constraint
     *
     * Return exception ModuleNotFoundException if module with specified constraints
     * could not be found in the list of modules installed
     *
     * @param string $name
     * @param string $version
     */
    protected function loadModule($name, $version = null) {
        $this->log->debug("    -> module: " . $name . ", version: " . ($version ? $version : 'any') . "");
        $this->log->debug("    -> module path: " . MODULE_PATH . '/' . $name . "/Module.inc");

        //require_once MODULE_PATH . '/' . $name . '/Module.inc';
        $moduleNS = "\Daw\Modules\\" . $name . "\Module";
        $module = new $moduleNS($this, $name);
        $this->modules[$name] = $module;

        // Load module information & configuration
        $module->load();
        $module->loadConfig($this->loadModuleConfig($name));

        //print_r($module->getInfo());

        return true;
    }

    protected function loadModuleConfig($name) {
        $this->log->debug("    o Load Module Config");
        $moduleConfFilePath = $this->basePath . '/Daw/conf/' . strtolower($name) . '.yml';
        if (file_exists($moduleConfFilePath)) {
            $this->log->debug("      - Using module configuration file: " . $moduleConfFilePath . "");
            $contents = file_get_contents($moduleConfFilePath);
            $this->config[$name] = $this->yaml->parse($contents);
        } else {
            $this->log->debug("      - No file $moduleConfFilePath found, using application base configuration file.");
        }

        $moduleConfig = isset($this->config[$name]) ? $this->config[$name] : array();
        $this->log->debug("      + Module config loaded: " . strlen(print_r($moduleConfig, true)) . " bytes.");

        return $moduleConfig;
    }

    // CONFIG

    public function config($section = null) {
        if ($section === null) {
            return $this->config;
        }

        return isset($this->config[$section]) ? $this->config[$section] : false;
    }

    public function getService() {
        return $this->service;
    }

    public function getRequest() {
        return $this->request;
    }

    // OBJECTS

    protected function loadObjects() {
        $nbObjects = 0;
        $this->log->debug("o Load Objects");
        foreach ($this->modules as $moduleName => $module) {
            $moduleObjects = $module->info('objects');
            if ($moduleObjects !== false) {
                foreach ($moduleObjects as $objectName => $objectInfo) {
                    $object = is_string($objectInfo) && $objectInfo !== null ? $objectInfo : $objectName;
                    $this->log->debug("  -> Module " . $moduleName . " publishes object $object");
                    if (!isset($this->objects[$object])) {
                        $this->objects[$object] = array();
                    }

                    $this->objects[$object][] = array(
                        'info' => $objectInfo,
                        'module' => $moduleName
                    );

                    $nbObjects++;
                }
            }
        }
        $this->log->debug("  + Objects loaded: " . $nbObjects . "");

    }

    /**
     * Return list of objects registered to the application
     *
     * @return array
     */
    public function getObjects() {
        return $this->objects;
    }

    /**
     * Return description of an object, if available on the application
     *
     * @param string $name
     */
    public function getObject($name) {
        return isset($this->objects[$name]) ? $this->objects[$name] : false;
    }

    public function getObjectStore($objectName) {
        $object = $this->getObject($objectName);
        $module = $this->getModule($object[0]['module']);

        return $module->store($objectName);
    }

    // OPERATIONS

    /**
     * Return list of all operations available in the application
     * for a given object
     *
     * @return array
     */
    public function getOperations($object = null) {
        $operationList = array();
        foreach ($this->modules as $module) {
            $moduleOperations = $module->operationList();
            foreach ($moduleOperations as $operation) {
                $operationInfo = $operation->info();
                $operationObject = isset($operationInfo['object']) ? $operationInfo['object'] : $module->getName();
                if ($object === null || $operationObject == $object) {
                        $operationList[] = array_merge(
                            array(
                                'label' => $operation->getName(),
                                'module' => $module->getName()
                            ),
                            $operation->info()
                        );
                }
            }
        }

        return $operationList;
    }

    /**
     * Return the operation for the given object and operation name,
     * false if not found
     *
     * @param string $object
     * @param string $name
     */
    public function getOperation($object, $name) {
        foreach ($this->modules as $module) {
            $moduleOperations = $module->operationList();
            foreach ($moduleOperations as $operation) {
                $operationInfo = $operation->info();
                $operationObject = isset($operationInfo['object']) ? $operationInfo['object'] : $module->getName();
                $operationName = isset($operationInfo['operation']) ? $operationInfo['operation'] : $operation->getName();
                if ($operationObject == $object && $operationName === $name) {
                    return $operation;
                }
            }
        }

        return false;
    }

    /* PROVIDERS */

    protected function loadProviders() {
        $nbProviders = 0;
        $this->log->debug("o Load Providers");
        foreach ($this->modules as $moduleName => $module) {
            foreach ($module->getProviders() as $feature) {
                $this->log->debug("  -> Module " . $moduleName . " provider loaded for feature $feature");
                $this->registerProvider($feature, $module);
                $nbProviders++;
            }
        }
        $this->log->debug("  + Providers loaded: " . $nbProviders . "");

        $this->log->debug("o Setting application providers");
        if (isset($this->config['providers'])) {
            foreach ($this->config['providers'] as $feature => $moduleName) {
                if (isset($this->modules[$moduleName])) {
                    $module = $this->modules[$moduleName];
                    $provider = $module->getProvider($feature);
                    if ($provider !== null) {
                        $this->register($provider, $feature);
                        $this->log->debug("  + Register " . get_class($provider) . " as $feature provider.");
                    }
                } else {
                    $this->log->debug("  ! No module $moduleName found for $feature provider.");
                }
            }
        }
    }

    /**
     * Return providers currently proposed by instance
     *
     * @return array
     */
    public function getProviders() {
        return $this->providers;
    }

    protected function registerProvider($feature, $module, $provider = null) {

        if (!isset($this->providers[$feature])) {
            $this->providers[$feature] = array();
        }

        if ($provider === null) {
            $provider = $module->getProvider($feature);
        }

        $this->providers[$feature][] = $provider;
        if (count($this->providers[$feature]) == 1) {
            $this->register($provider, $feature);
        }

        $featureConfFilePath = $this->basePath . '/conf/' . strtolower($feature) . '.yml';
        if (file_exists($featureConfFilePath)) {
            $this->log->debug("      - Using provider feature configuration file: " . $featureConfFilePath . "");
            $contents = file_get_contents($featureConfFilePath);
            $this->config[$feature] = $this->yaml->parse($contents);
        }
    }


    // FORMATTERS

    protected function loadFormatters() {
        $nbFormatters = 0;
        $this->log->info("o Load Formatters");
        foreach ($this->modules as $moduleName => $module) {
            if ($module->info('formatters') !== false) {
                if ($module->info('formatters')) {
                    foreach ($module->info('formatters') as $formatter) {
                        $this->log->debug("  -> Module " . $moduleName . " formatter $formatter loaded.");
                        $this->formatters["$moduleName.$formatter"] = array(
                            'name' => $formatter,
                            'module' => $moduleName,
                            'instance' => null
                        );
                        $nbFormatters++;
                    }
                }
            }
        }

        $this->log->debug("  + Formatters loaded: " . $nbFormatters . "");

        // Load base formatters
        $this->formatters["Json"] = array(
            'name' => 'Json',
            'module' => null,
            'instance' => new JsonFormatter($this)
        );
        $this->formatters["TextIndent"] = array(
                    'name' => 'TextIndent',
                    'module' => null,
                    'instance' => new TextIndentFormatter($this)
        );

    }

    public function getFormatter($object, $format) {
        foreach ($this->formatters as $formatter) {
            if ($formatter['instance'] === null) {
                //require_once MODULE_PATH . '/' . $formatter['module'] . '/formatters/' . $formatter['name'] . '.inc';
                $formatterNS = "\Daw\\Modules\\" . $formatter['module'] . "\\Formatters\\" . $formatter['name'];
                $formatter['instance'] = new $formatterNS($this);
            }

            if ($formatter['instance']->isFormatterFor($object, $format)) {
                return $formatter['instance'];
            }
        }

        return false;
    }

    public function render($object, $format, $output = false) {
        $this->log->trace(" --- render(" . (is_object($object) ? get_class($object) : (is_array($object) ? 'array' : $object)) . ", $format) ");
        $formatter = $this->getFormatter($object, $format);

        if ($formatter === false) {
            throw new \Daw\Core\Exception\Exception("No formatter found for object of class " . get_class($object) . ".");
        }

        $this->log->trace(" --- use formatter: " . get_class($formatter));
        $formatter->setContext($this->context);
        $contents = $formatter->render($object, $format);
        if ($output === true) {
            print $contents;
        }

        return $contents;
    }

    protected function init() {

        $this->basePath = PROJECT_BASEPATH;

        $this->register(new NullProvider($this), 'log');

        // Register some libraries
        $this->register(new \Symfony\Component\Yaml\Yaml(), 'yaml');

        $cacheProviderClass = "\Daw\\Providers\\CacheProvider";
        $logProviderClass = "\Daw\\Providers\\LogProvider";
        $securityProviderClass = "\Daw\\Providers\\SecurityProvider";

        $this->registerProvider('cache', null, new $cacheProviderClass($this));
        $this->registerProvider('log', null, new $logProviderClass($this));
        $this->registerProvider('security', null, new $securityProviderClass($this));

        // Load
        $this->loadConfig();
        $this->loadModules();
        $this->loadProviders();
        $this->loadObjects();
        $this->loadFormatters();
    }

    /**
     * Call operation as application owner
     *
     * No authentication or access will be required in this context
     * for all calls performed till we exit the sudoed call
     */
    public function sudo($name, $operation, $params = array()) {
        static $sudo = 0;

        $this->register(true, 'sudo');
        $sudo++;

        $response = $this->call($name, $operation, $params, true);

        $sudo--;
        $this->register($sudo === 0, 'sudo');

        return $response;
    }

    /**
     * Call operation for one object
     *
     * @param string $object
     * @param string $operation
     * @param array $args
     */
    public function call($name, $operation, $params = array(), $system = false) {

        $this->log->debug("o Initiate call($name, $operation)");

        $module = null;
        $object = null;

        // Verifies that object exists
        if (isset($this->objects[$name])) {
            $this->log->debug("  o Call on object $name requested");
            $object = $name;

            // Now find module serving operation for this object
            foreach ($this->objects[$name] as $objectName => $objectData) {
                $moduleName = $objectData['module'];
                $moduleInstance = $this->modules[$moduleName];
                $moduleOperations = $moduleInstance->info('operations');
                foreach ($moduleOperations as $operationInfo) {
                    if (isset($operationInfo['object']) && $operationInfo['object'] == $object
                        && isset($operationInfo['operation']) && $operationInfo['operation'] == $operation) {
                        $module = $moduleName;
                        break;
                    }
                }
            }
        }

        if ($module === null) {
            if (isset($this->modules[$name])) {
                $this->log->debug("  o Call on module $name requested");
                $module = $name;
                $object = null;
            }
        }

        if ($module === null) {
            throw new \Daw\Core\Exception\Exception("No module found serving operation $operation for object $object.");
        }

        // Check is module restriction has been set for the operation
        $operationSeparatorPos = strpos($operation, '.');
        if ($operationSeparatorPos !== false) {
            $moduleToken = substr($operation, 0, $operationSeparatorPos);
            $operationToken = substr($operation, $operationSeparatorPos);
            if ($module !== null && $moduleToken != $module) {
                // conflict between module retsriction
                throw new \Daw\Core\Exception\Exception('Conflict between modules requested.');
            }

            $module = $moduleToken;
            $operation = $operationToken;
        }

        $this->log->debug("    !! module: $module");
        $this->log->debug("    !! object: $object");
        $this->log->debug("    !! operation: $operation");

        $response = $this->callModule($module, $object, $operation, $params, $system);
        if ($system) {
            return $response;
        }

        $this->response->success = true;
        $this->response->contents = $response;
    }

    /**
     * Call module operation
     *
     * @param string $module
     * @param string $object
     * @param string $operation
     * @param array params
     * @param boolean system
     * @return object
     */
    protected function callModule($module, $object, $operation, $params = array(), $system = false) {

        // Check that module exists
        if ($module === null) {
            throw new \Daw\Core\Exception\Exception("No Module specified in the call.");
        }

        if (!isset($this->modules[$module])) {
            throw new \Daw\Core\Exception\Exception("Module $module not installed.");
        }

        if (!$this->sudo && $this->security->hasAccess($module, $object, $operation) !== true) {
            throw new \Daw\Core\Exception\Exception("You are not authorized to access this operation ($module, $object, $operation).");
        }

        $moduleInstance = $this->modules[$module];

        $response = $moduleInstance->call($object, $operation, $params);

        return $response;
    }

    /**
     * Start processing
     *
     * @param Service $service
     */
    public function start($service = null) {

        $this->service = $service;
        $this->request = $service->getRequest();
        $this->response = $service->buildResponse();
        $this->response->setRequest($this->request);

        $args = $this->request->getArgs();

        $object = isset($args['OBJECT']) && !empty($args['OBJECT']) ? $args['OBJECT'] : $this->config['defaultObject'];
        $operation = isset($args['OPERATION']) && !empty($args['OPERATION']) ? $args['OPERATION'] : $this->config['defaultOperation'];


        // Catch internal params
        $systemParams = array();
        $params = array();

        foreach (isset($args['PARAMS']) && !empty($args['PARAMS']) ? $args['PARAMS'] : array() as $param => $value) {
            if ($param[0] === '_') {
                $systemParams[substr($param, 1)] = $value;
            } else {
                $params[$param] = $value;
            }
        }

        try {
            // Authenticate user
            $this->register($this->security->authenticate($this->request->getAuthenticationToken()), 'user');

            // Trigger call
            $this->call($object, $operation, $params);
        } catch (\Exception $e) {
            $this->log->debug(' !!! Exception !!!');
            $this->log->debug($e->getTraceAsString());

            $this->response->success = false;
            $this->response->code = $e->getCode();
            $this->response->message = $e->getMessage();
            $this->response->contents = $e;
        }

        $this->register(new FormatterContext(), 'context');
        $this->render($this->response, isset($systemParams['format']) ? $systemParams['format'] : $this->service->getResponseFormat(), true);
    }

    // FILESYSTEM

    const PATH_BASE = 'PATH_BASE';
    const PATH_FILES = 'PATH_FILES';

    public function path($filename, $path = self::PATH_BASE) {
        switch ($path) {
            case self::PATH_FILES:
                return FileUtil::concat($this->basePath, '/var/run', $filename);
                break;
            case self::PATH_BASE:
            default:
                return FileUtil::concat($this->basePath, $filename);
                break;
        }
    }
}

/**
 * Return Core instance
 *
 * @return Core
 */
function core() {
    return Core::instance();
}
