import plotly
import plotly.graph_objects as go
import sys

# grafico : tamanho x tempo, histograma de taxa de proximidade
# talvez tamanho x taxa?? sla

def main():
    n=0

    s = ''
    alg = ''
    s = 'brkga'; alg = 'BRKGA'

    f = open('data/optimal')
    optimal = {}
    for line in f.readlines():
        a,b = line.split(' ')
        optimal[a] = int(b[:-1])
    f.close()

    f = open('data/'+s+'.txt')
    data = {}
    for line in f.readlines():
        file,n,ans,t = line.split(' ')
        if file[:-4] in optimal: data[file] = int(n),int(ans),int(t[:-1])

    sz = []
    time = []
    for i in data:
        sz.append(data[i][0])
        time.append(data[i][2]/1000)
    sorted_pairs = sorted(zip(sz, time))
    sz,time = zip(*sorted_pairs)

    fig = go.Figure(data=[go.Scatter(x=sz, y=time)])
    fig.update_layout(
        title={
            'text':'Number of points x execution time using the '+alg+' algorithm',
            'x':0.5,
            'xanchor': 'center'},
        xaxis_title='Number of points',
        yaxis_title='Execution time (seconds)',
        width=750,
        height=700,
        shapes=[dict(
            type='rect',
            x0=0, x1=1, y0=0, y1=1,
            xref='paper', yref='paper',
            line=dict(
                color='black',
                width=1
            )
        )],
        xaxis=dict(showline=True, linewidth=2, linecolor='black'),  # Border around the x-axis
        yaxis=dict(showline=True, linewidth=2, linecolor='black'),
    )
    # plotly.offline.plot(fig, filename='images/SizeXTime_'+s+'.png')

    image_bytes = fig.to_image(format="png")
    with open('images/SizeXTime_'+s+'.png', "wb") as f:
        f.write(image_bytes)

    rate = []
    for i in optimal:
        rate.append(data[i+'.tsp'][1]/optimal[i])
        if data[i+'.tsp'][1]/optimal[i] > 5:
            print(i,data[i+'.tsp'][1],optimal[i])
    fig = go.Figure(
            data=[go.Histogram(x=rate,nbinsx=16,
                marker=dict(
                    color='red',
                    line=dict(
                    color='black',
                    width=1
                )
            )
        )
    ])

    fig.update_layout(
        title={
            'text' :'Average approximation to optimal cost using the '+alg+' algorithm',
            'x':0.5,
            'xanchor': 'center'
        },
        xaxis_title='Approximation to optimal cost (cost found/optimal)',
        yaxis_title='Number of occurences',
        width=750,
        height=700,
        bargap=0,
        shapes=[dict(
            type='rect',
            x0=0, x1=1, y0=0, y1=1,
            xref='paper', yref='paper',
            line=dict(
                color='black',
                width=1
            )
        )],
        xaxis=dict(showline=True, linewidth=2, linecolor='black'),  # Border around the x-axis
        yaxis=dict(showline=True, linewidth=2, linecolor='black')
    )
    image_bytes = fig.to_image(format="png")
    with open('images/AverageApproximation_'+s+'.png', "wb") as f:
        f.write(image_bytes)
    # plotly.offline.plot(fig, filename='images/AverageApproximation_'+s+'.png')

if __name__ == '__main__': main()