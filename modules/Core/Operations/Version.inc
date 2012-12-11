<?php

namespace Daw\Modules\Core\Operations;

class Version extends \Daw\Core\Module\Operation {

	public function run($args = array()) {
		$info = $this->core->config();

		return $info['version'];
	}
}
