import yfinance as yf
import pandas as pd

# Define the stock ticker and the data range
ticker = 'AAPL'  # Example: Apple stock
start_date = '2022-01-01'
end_date = '2023-01-01'

# Download stock data
data = yf.download(ticker, start=start_date, end=end_date)

# Save the data to a CSV file
csv_filename = 'stock_data.csv'
data.to_csv(csv_filename)

print(f"Data saved to {csv_filename}")
