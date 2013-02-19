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

use \Daw\Core\Service\ServiceResponse;

/**
 * Service response default formatter
 *
 * This formatter can be used to render any ServiceResponse instance
 * It renders the service response using an array of following elements:
 *   - success: a boolean
 *   - code: an integer
 *   - message: potential message associated to a failure case or a success
 *   - data: any additional contents provided in the response
 *
 * @package Modules/Core
 * @subpackage Formatters
 * @author Axel Tessier <axel.tessier@extendev.net>
 * @version $Id: Event.inc 112 2003-08-22 06:22:40Z  $
 */
class ServiceResponseFormatter extends \Daw\Core\Formatter\Formatter {

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
        return $object instanceof ServiceResponse;
    }

    /**
     * Render service response method
     *
     * @param object $object object to render
     * @param Daw\Core\Formatter\Format $format format to be used for rendering
     * @return string the JSON string
     */
    public function render($object, $format) {

        $data = array(
            'success' => ($object->success ? 'TRUE' : 'FALSE'),
            'code' => $object->code,
            'message' => $object->message,
            'data' => $object->contents
        );

        switch ($format) {
            case 'TextIndent':
                return $this->renderTextIndent($data);
                break;
            case 'Json':
                return $this->renderJson($data);
                break;
        }
    }

    /**
     * Text indented render method
     *
     * @param object $object object to render
     * @return string the text indented string
     */
    protected function renderTextIndent($object) {
        return $this->core->render($object, 'TextIndent');
    }

    /**
     * JSON render method
     *
     * @param object $object object to render
     * @return string the JSON string
     */
    protected function renderJson($object) {
        return $this->core->render($object, 'Json');
    }
}
