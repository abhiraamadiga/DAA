import React, { useState, useRef, useEffect } from 'react';
import { Terminal, CheckCircle, Code2, Zap, Activity } from 'lucide-react';
import { SmallestRangeForm, LineIntersectionForm, MSISForm } from './components/Forms';

function App() {
  const [activeTab, setActiveTab] = useState(1);
  const [loading, setLoading] = useState(false);
  const [result, setResult] = useState(null);
  const terminalRef = useRef(null);

  useEffect(() => {
    if (terminalRef.current) {
      terminalRef.current.scrollTop = terminalRef.current.scrollHeight;
    }
  }, [result]);

  const runAlgorithm = async (inputSequence) => {
    setLoading(true);
    setResult(null);
    try {
      const response = await fetch('http://localhost:3001/api/run', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ input_sequence: inputSequence })
      });
      const data = await response.json();
      setResult(data);
    } catch (error) {
      console.error(error);
      setResult({ stdout: '', stderr: 'Failed to connect to backend server. Is it running on port 3001?', code: -1 });
    } finally {
      setLoading(false);
    }
  };

  const parseResult = (stdout, tab) => {
    if (!stdout) return null;
    const lines = stdout.split('\n');
    
    if (tab === 1) {
      const match = lines.find(l => l.includes('Smallest range including'));
      return match ? match.split(': ')[1] : null;
    }
    if (tab === 2) {
      const match = lines.find(l => l.includes('Total intersections:'));
      return match ? match.split(': ')[1] : null;
    }
    if (tab === 3) {
      const sumMatch = lines.find(l => l.includes('Maximum sum:'));
      const subMatch = lines.find(l => l.includes('MSIS subsequence:'));
      if (sumMatch && subMatch) {
        return (
          <div>
            <div><strong>Sum:</strong> {sumMatch.split(': ')[1]}</div>
            <div><strong>Subsequence:</strong> {subMatch.split(': ')[1]}</div>
          </div>
        );
      }
    }
    return null;
  };

  const parsedHighlight = result ? parseResult(result.stdout, activeTab) : null;

  return (
    <div className="app-container">
      <header className="header">
        <h1>DAA Visualizer Pro</h1>
        <p>Interactive Algorithm Execution Environment</p>
      </header>

      <div className="nav-cards">
        <div className={`nav-card ${activeTab === 1 ? 'active' : ''}`} onClick={() => { setActiveTab(1); setResult(null); }}>
          <Zap size={18} style={{ marginBottom: '-3px', marginRight: '6px' }} /> Smallest Range (Heap)
        </div>
        <div className={`nav-card ${activeTab === 2 ? 'active' : ''}`} onClick={() => { setActiveTab(2); setResult(null); }}>
          <Code2 size={18} style={{ marginBottom: '-3px', marginRight: '6px' }} /> Line Intersection (Sweep Line)
        </div>
        <div className={`nav-card ${activeTab === 3 ? 'active' : ''}`} onClick={() => { setActiveTab(3); setResult(null); }}>
          <Activity size={18} style={{ marginBottom: '-3px', marginRight: '6px' }} /> MSIS (DP)
        </div>
      </div>

      <div className="main-grid">
        <div className="glass-panel" style={{ height: 'fit-content' }}>
          <h2 style={{ marginBottom: '1.5rem', display: 'flex', alignItems: 'center', gap: '0.5rem' }}>
            {activeTab === 1 && "Smallest Range Setup"}
            {activeTab === 2 && "Line Intersection Setup"}
            {activeTab === 3 && "MSIS Setup"}
          </h2>
          
          {activeTab === 1 && <SmallestRangeForm onSubmit={runAlgorithm} loading={loading} />}
          {activeTab === 2 && <LineIntersectionForm onSubmit={runAlgorithm} loading={loading} />}
          {activeTab === 3 && <MSISForm onSubmit={runAlgorithm} loading={loading} />}
        </div>

        <div className="glass-panel" style={{ display: 'flex', flexDirection: 'column' }}>
          <h2 style={{ marginBottom: '1.5rem', display: 'flex', alignItems: 'center', gap: '0.5rem' }}>
            <Terminal size={24} color="var(--accent-primary)" /> Execution Output
          </h2>
          
          {parsedHighlight && (
            <div className="result-highlight fade-in">
              <div style={{ fontSize: '0.8rem', color: 'var(--accent-primary)', textTransform: 'uppercase', letterSpacing: '1px', marginBottom: '0.25rem' }}>
                Extracted Result
              </div>
              {parsedHighlight}
            </div>
          )}

          <div className="terminal" ref={terminalRef} style={{ flexGrow: 1 }}>
            <div className="terminal-header">
              <div className="terminal-dot dot-red"></div>
              <div className="terminal-dot dot-yellow"></div>
              <div className="terminal-dot dot-green"></div>
            </div>
            {result ? (
              <div className="fade-in">
                {result.stdout && <div>{result.stdout}</div>}
                {result.stderr && <div style={{ color: 'var(--danger)' }}>{result.stderr}</div>}
                {result.code !== 0 && result.code !== undefined && (
                  <div style={{ color: 'var(--danger)', marginTop: '1rem' }}>
                    Process exited with code {result.code}
                  </div>
                )}
                {result.code === 0 && (
                  <div style={{ color: 'var(--success)', marginTop: '1rem', display: 'flex', alignItems: 'center', gap: '0.5rem' }}>
                    <CheckCircle size={16} /> Execution completed successfully
                  </div>
                )}
              </div>
            ) : (
              <div style={{ color: 'var(--text-muted)', fontStyle: 'italic' }}>
                Awaiting execution... Output will appear here.
              </div>
            )}
          </div>
        </div>
      </div>
    </div>
  );
}

export default App;
