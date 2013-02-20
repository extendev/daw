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

use \Daw\Core\Service\Api\ApiServiceResponse;
use \Daw\Core\Service\Http\HttpServiceResponse;

/**
 * Web service response default formatter
 * This formatter can be used to render web dedicated service responses 
 * like ApiServiceResponse and HttpServiceResponse
 *
 * @package Modules\Core
 * @subpackage Formatters
 * @author Axel Tessier <axel.tessier@extendev.net>
 * @version $Id: Event.inc 112 2003-08-22 06:22:40Z  $
 */
class WebServiceResponseFormatter extends \Daw\Core\Formatter\Formatter {

    /**
     * Return true if formatter supports given object and possibly given format
     *
     * This formatter accepts any ApiServiceResponse or HttpServiceResponse object
     *
     * @param object $object object to render
     * @param Daw\Core\Formatter\Format $format format to be used for rendering
     * @return boolean
     */
    public function isFormatterFor($object, $format = null) {
        return $object instanceof ApiServiceResponse || $object instanceof HttpServiceResponse;
    }

    /**
     * Render service response method
     *
     * @param object $object object to render
     * @param Daw\Core\Formatter\Format $format format to be used for rendering
     * @return string the JSON string
     */
    public function render($object, $format) {

        if (!$object->success) {
            if ($object->code) {
                header('HTTP/1.0 ' . $object->code  . ' Error');
            }

            switch ($object->code) {
                case 401:
                    header('WWW-Authenticate: Basic realm="Daw"');
                    break;
            }

            return $this->core->render($object->contents, $format);
        }

        return $this->core->render($object->contents, $format);
    }
}
