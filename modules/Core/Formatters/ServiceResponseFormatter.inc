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

use Daw\Core\Service\ServiceResponse;

class ServiceResponseFormatter extends \Daw\Core\Formatter\Formatter {

	/**
	 * Return TRUE if formatter supports given object and possibly given format
	 *
	 * Enter description here ...
	 * @param mixed $object
	 * @param string $format
	 */
	public function isFormatterFor($object, $format = null) {
		return $object instanceof ServiceResponse;
	}

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

	protected function renderTextIndent($object) {
		return $this->core->render($object, 'TextIndent');
	}

	protected function renderJson($object) {
		return $this->core->render($object, 'Json');
	}
}