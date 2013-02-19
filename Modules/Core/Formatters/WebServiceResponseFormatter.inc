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

class WebServiceResponseFormatter extends \Daw\Core\Formatter\Formatter {

    /**
     * Return TRUE if formatter supports given object and possibly given format
     *
     * Enter description here ...
     * @param mixed $object
     * @param string $format
     */
    public function isFormatterFor($object, $format = null) {
        return $object instanceof ApiServiceResponse || $object instanceof HttpServiceResponse;
    }

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
