<?php

defined('BASEPATH') or exit('No direct script access allowed');

class Data extends CI_Controller
{
    public function simpan()
    {
        $tinggiAir = $this->input->get('tinggiAir');
        $tinggiLimpasan = $this->input->get('tinggiLimpasan');

        $result = '';

        if ($tinggiAir != '') {
            $data = [
                'tinggiAir' => $tinggiAir,
                'tinggiLimpasan' => $tinggiLimpasan
            ];

            $this->db->order_by('id', 'desc');
            $cek = $this->db->get('data', 1)->row();

            if ($cek->tinggiAir != $tinggiAir) {
                $insert = $this->db->insert('data', $data);

                if ($insert) {
                    $result = 'Data berhasil disimpan';
                } else {
                    $result = 'Server Error';
                }
            } else {
                $result = 'Data masih sama';
            }
        } else {
            $result = 'Tinggi air tidak boleh kosong';
        }

        $kontrol = $this->db->get('kontrol', 1)->row();

        echo json_encode([
            'status' => $result,
            'pompa' => $kontrol->pompa
        ]);
    }
}

/* End of file Data.php */
