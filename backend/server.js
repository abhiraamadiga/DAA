const express = require('express');
const cors = require('cors');
const { spawn } = require('child_process');
const path = require('path');

const app = express();
app.use(cors());
app.use(express.json());

// Path to the C executable
const EXE_PATH = path.join(__dirname, '..', 'daa_project.exe');

app.post('/api/run', (req, res) => {
    const { input_sequence } = req.body;

    if (!input_sequence) {
        return res.status(400).json({ error: 'input_sequence is required' });
    }

    console.log(`Running with input:\n${input_sequence}`);

    // Spawn the executable
    const child = spawn(EXE_PATH, [], { cwd: path.join(__dirname, '..') });

    let stdout = '';
    let stderr = '';

    child.stdout.on('data', (data) => {
        stdout += data.toString();
    });

    child.stderr.on('data', (data) => {
        stderr += data.toString();
    });

    child.on('error', (err) => {
        console.error('Failed to start subprocess.', err);
        return res.status(500).json({ error: 'Failed to execute the C program', details: err.message });
    });

    child.on('close', (code) => {
        console.log(`Child process exited with code ${code}`);
        res.json({
            stdout,
            stderr,
            code
        });
    });

    // Write input sequence to stdin
    child.stdin.write(input_sequence);
    child.stdin.end(); // Close stdin to signal end of input
});

const PORT = 3001;
app.listen(PORT, () => {
    console.log(`Backend server running on http://localhost:${PORT}`);
});
