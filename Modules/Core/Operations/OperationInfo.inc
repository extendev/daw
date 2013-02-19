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

use \Daw\Core\Exception\OperationException;
use \Daw\Core\Exception\OperationArgumentException;

/**
 * Operation Info Operation
 * Return information about an operation as defined in Module's module.info file
 *
 * @package Modules/Core
 * @subpackage Operations
 * @author Axel Tessier <axel.tessier@extendev.net>
 * @version $Id: Event.inc 112 2003-08-22 06:22:40Z  $
 */
class OperationInfo extends \Daw\Core\Module\Operation {

    /**
     * Run the operation
     *
     * @param $args arguments
     * @return string response validating deletion of the site
     * @see Daw\Core\Module.Operation::run()
     */
    public function run($args = array()) {
        $this->validate($args);

        $operation = $this->core->getOperation($args['object'], $args['operation']);
        if ($operation === false) {
            throw new OperationException($this, 'No operation found for given arguments', 405);
        }

        return $operation->info();
    }
}
