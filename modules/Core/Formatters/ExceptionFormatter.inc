<?php

/*
 * This file is part of the Daw package.
 *
 * (c) Axel Tessier <axel.tessier@extendev.net>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace Daw\Modules\Core\Formatters;

use \Daw\Core\Exception\Exception;

/**
 * Daw - JSON Default Formatter
 *
 * This formatter supports any type of objects
 *
 * @author Axel Tessoer / Extendev
 * @version $Id$
 */
class ExceptionFormatter extends \Daw\Core\Formatter\Formatter {

    /**
     * Return TRUE if formatter supports given object and possibly given format
     *
     * @param unknown_type $object
     * @param unknown_type $format
     */
    public function isFormatterFor($object, $format = null) {
    	return $object instanceof Exception;
    }

    /**
     * Render object in JSON format
     */
    public function render($object, $format) {
    	return $this->core->render($object->getData(), $format);
    }
}
