<div class="row mt-3">
	<div class="col-lg-6">
		<div class="card">
			<div class="card-body">
				<form action="<?= base_url('kontrol/update'); ?>" method="POST">
					<div class="form-group">
						<label>Status Pompa</label>
						<input type="hidden" name="id" value="<?= $kontrol->id; ?>">
						<select name="pompa" class="form-control">
							<option value="ON" <?= ($kontrol->pompa == 'ON') ? 'selected' : ''; ?>>ON</option>
							<option value="OFF" <?= ($kontrol->pompa == 'OFF') ? 'selected' : ''; ?>>OFF</option>
						</select>
					</div>
					<button type="submit" class="btn btn-info">Simpan</button>
				</form>
			</div>
		</div>
	</div>
</div>