<?php

/**
 * This file is part of the Daw package.
 *
 * (c) Axel Tessier <axel.tessier@extendev.net>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this module source code.
 */

namespace Daw\Modules\Core\Operations;

use \Daw\Core\Exception\Exception;

/**
 * Module Info Operation
 * Return Module's module.info file contents
 *
 * @package Modules\Core
 * @subpackage Operations
 * @author Axel Tessier <axel.tessier@extendev.net>
 * @version $Id: Event.inc 112 2003-08-22 06:22:40Z  $
 */
class ModuleInfo extends \Daw\Core\Module\Operation {

    /**
     * Run the operation
     *
     * @param $args arguments
     * @return string response validating deletion of the site
     * @see Daw\Core\Module.Operation::run()
     */
    public function run($args = array()) {
        if (!isset($args['name'])) {
            throw new Exception('Module name is required', 301);
        }

        $module = $this->core->getModule($args['name']);
        if ($module === false) {
            throw new Exception('Module could not be found', 302);
        }

        return $module->info();
    }
}
