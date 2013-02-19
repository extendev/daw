<?php

/**
 * This file is part of the Daw package.
 *
 * (c) Axel Tessier <axel.tessier@extendev.net>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace Daw\Modules\Core\Formatters;

/**
 * Operation default formatter
 * This formatter can be used to render any Operation object
 *
 * @package Modules/Core
 * @subpackage Formatters
 * @author Axel Tessier <axel.tessier@extendev.net>
 * @version $Id: Event.inc 112 2003-08-22 06:22:40Z  $
 */
class OperationFormatter extends \Daw\Core\Formatter\Formatter {

    /**
     * Return true if formatter supports given object and possibly given format
     *
     * This formatter accepts any object provided that requested format is TextIndent
     *
     * @param object $object object to render
     * @param Daw\Core\Formatter\Format $format format to be used for rendering
     * @return boolean
     */
    public function isFormatterFor($object, $format = null) {
        return $object instanceof \Daw\Core\Object\Operation;
    }

    /**
     * Render service response method
     *
     * @param object $object object to render
     * @param Daw\Core\Formatter\Format $format format to be used for rendering
     * @return string the JSON string
     */
    public function render($object, $format) {
    }
}
