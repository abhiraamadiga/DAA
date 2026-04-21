import React, { useState } from 'react';
import { Plus, Trash2, Play, Activity } from 'lucide-react';

export function SmallestRangeForm({ onSubmit, loading }) {
  const [useSample, setUseSample] = useState(true);
  const [arrays, setArrays] = useState(['4 7 9 12 15', '0 8 10 14 20', '6 12 16 30 50']);

  const handleAdd = () => setArrays([...arrays, '']);
  const handleRemove = (i) => setArrays(arrays.filter((_, idx) => idx !== i));
  const handleChange = (i, val) => {
    const newArr = [...arrays];
    newArr[i] = val;
    setArrays(newArr);
  };

  const handleSubmit = (e) => {
    e.preventDefault();
    if (useSample) {
      onSubmit('1\ny\n4\n');
    } else {
      let seq = `1\nn\n${arrays.length}\n`;
      arrays.forEach(arr => {
        seq += `${arr.trim()}\n`;
      });
      seq += '4\n';
      onSubmit(seq);
    }
  };

  return (
    <form onSubmit={handleSubmit} className="fade-in">
      <div className="input-group">
        <label>Input Mode</label>
        <div style={{ display: 'flex', gap: '1rem' }}>
          <button type="button" className={`btn ${useSample ? '' : 'btn-secondary'}`} onClick={() => setUseSample(true)}>Sample Data</button>
          <button type="button" className={`btn ${!useSample ? '' : 'btn-secondary'}`} onClick={() => setUseSample(false)}>Custom Data</button>
        </div>
      </div>

      {!useSample && (
        <div className="input-group">
          <label>Arrays (space-separated integers)</label>
          <div className="dynamic-list">
            {arrays.map((arr, i) => (
              <div key={i} className="dynamic-item">
                <input required className="form-control" value={arr} onChange={e => handleChange(i, e.target.value)} placeholder="e.g. 1 5 10 15" />
                {arrays.length > 1 && (
                  <button type="button" className="remove-btn" onClick={() => handleRemove(i)}>
                    <Trash2 size={16} />
                  </button>
                )}
              </div>
            ))}
          </div>
          <button type="button" className="btn btn-secondary" style={{ width: 'auto', padding: '0.5rem 1rem' }} onClick={handleAdd}>
            <Plus size={16} /> Add Array
          </button>
        </div>
      )}

      <button type="submit" className="btn" disabled={loading}>
        {loading ? <div className="spinner"></div> : <><Play size={18} /> Run Algorithm</>}
      </button>
    </form>
  );
}

export function LineIntersectionForm({ onSubmit, loading }) {
  const [useSample, setUseSample] = useState(true);
  const [horizontals, setHorizontals] = useState(['1 5 2', '2 7 4']);
  const [verticals, setVerticals] = useState(['3 1 5']);

  const handleSubmit = (e) => {
    e.preventDefault();
    if (useSample) {
      onSubmit('2\ny\n4\n');
    } else {
      let seq = `2\nn\n${horizontals.length}\n`;
      horizontals.forEach(h => seq += `${h.trim()}\n`);
      seq += `${verticals.length}\n`;
      verticals.forEach(v => seq += `${v.trim()}\n`);
      seq += '4\n';
      onSubmit(seq);
    }
  };

  const updateList = (list, setter, idx, val) => {
    const arr = [...list];
    arr[idx] = val;
    setter(arr);
  };
  const removeList = (list, setter, idx) => setter(list.filter((_, i) => i !== idx));

  return (
    <form onSubmit={handleSubmit} className="fade-in">
      <div className="input-group">
        <label>Input Mode</label>
        <div style={{ display: 'flex', gap: '1rem' }}>
          <button type="button" className={`btn ${useSample ? '' : 'btn-secondary'}`} onClick={() => setUseSample(true)}>Sample Data</button>
          <button type="button" className={`btn ${!useSample ? '' : 'btn-secondary'}`} onClick={() => setUseSample(false)}>Custom Data</button>
        </div>
      </div>

      {!useSample && (
        <div style={{ display: 'grid', gridTemplateColumns: '1fr 1fr', gap: '1rem' }}>
          <div className="input-group">
            <label>Horizontal Segments (x1 x2 y)</label>
            <div className="dynamic-list">
              {horizontals.map((h, i) => (
                <div key={i} className="dynamic-item">
                  <input required className="form-control" value={h} onChange={e => updateList(horizontals, setHorizontals, i, e.target.value)} placeholder="x1 x2 y" />
                  <button type="button" className="remove-btn" onClick={() => removeList(horizontals, setHorizontals, i)}><Trash2 size={16} /></button>
                </div>
              ))}
            </div>
            <button type="button" className="btn btn-secondary" style={{ width: 'auto', padding: '0.5rem 1rem' }} onClick={() => setHorizontals([...horizontals, ''])}>
              <Plus size={16} /> Add Horizontal
            </button>
          </div>

          <div className="input-group">
            <label>Vertical Segments (x y1 y2)</label>
            <div className="dynamic-list">
              {verticals.map((v, i) => (
                <div key={i} className="dynamic-item">
                  <input required className="form-control" value={v} onChange={e => updateList(verticals, setVerticals, i, e.target.value)} placeholder="x y1 y2" />
                  <button type="button" className="remove-btn" onClick={() => removeList(verticals, setVerticals, i)}><Trash2 size={16} /></button>
                </div>
              ))}
            </div>
            <button type="button" className="btn btn-secondary" style={{ width: 'auto', padding: '0.5rem 1rem' }} onClick={() => setVerticals([...verticals, ''])}>
              <Plus size={16} /> Add Vertical
            </button>
          </div>
        </div>
      )}

      <button type="submit" className="btn" disabled={loading} style={{ marginTop: '1rem' }}>
        {loading ? <div className="spinner"></div> : <><Play size={18} /> Run Algorithm</>}
      </button>
    </form>
  );
}

export function MSISForm({ onSubmit, loading }) {
  const [useSample, setUseSample] = useState(true);
  const [arrayStr, setArrayStr] = useState('1 101 2 3 100 4 5');

  const handleSubmit = (e) => {
    e.preventDefault();
    if (useSample) {
      onSubmit('3\ny\n4\n');
    } else {
      onSubmit(`3\nn\n${arrayStr.trim()}\n4\n`);
    }
  };

  return (
    <form onSubmit={handleSubmit} className="fade-in">
      <div className="input-group">
        <label>Input Mode</label>
        <div style={{ display: 'flex', gap: '1rem' }}>
          <button type="button" className={`btn ${useSample ? '' : 'btn-secondary'}`} onClick={() => setUseSample(true)}>Sample Data</button>
          <button type="button" className={`btn ${!useSample ? '' : 'btn-secondary'}`} onClick={() => setUseSample(false)}>Custom Data</button>
        </div>
      </div>

      {!useSample && (
        <div className="input-group fade-in">
          <label>Array Elements (space-separated)</label>
          <input required className="form-control" value={arrayStr} onChange={e => setArrayStr(e.target.value)} placeholder="e.g. 1 101 2 3 100" />
        </div>
      )}

      <button type="submit" className="btn" disabled={loading}>
        {loading ? <div className="spinner"></div> : <><Play size={18} /> Run Algorithm</>}
      </button>
    </form>
  );
}
