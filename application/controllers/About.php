<?php

defined('BASEPATH') or exit('No direct script access allowed');

class About extends CI_Controller
{
	public function index()
	{
		$data = [
			'title' => 'About Us',
			'page' => 'about'
		];

		$this->load->view('index', $data);
	}
}

/* End of file About.php */
