<h1>Matrix Multiplication using Producer-Consumer Model</h1>

<p>This C code demonstrates matrix multiplication utilizing a producer-consumer model implemented with pthreads and semaphores.</p>

<h2>Description</h2>

<p>The program generates two random matrices, A and B, and performs matrix multiplication (A * B) using multiple producer threads for computation and a single consumer thread to assemble the resultant matrix.</p>

<h2>Prerequisites</h2>

<p>Ensure you have a C compiler installed to compile and run the code.</p>

<h2>Usage</h2>

<ol>
  <li>Clone the repository or download the C file.</li>
  <li>Compile the code using a C compiler. For example:</li>
</ol>

<pre><code>gcc -o matrix_multiplication matrix_multiplication.c -pthread
</code></pre>

<ol start="3">
  <li>Run the compiled executable:</li>
</ol>

<pre><code>./matrix_multiplication
</code></pre>

<h2>Implementation Details</h2>

<ul>
  <li><strong>Functions:</strong></li>
  <ul>
    <li><code>generate()</code>: Generates random matrices A and B with specified sizes and fills them with random values. Displays the generated matrices.</li>
    <li><code>producer()</code>: Performs the product of specific rows and columns from matrices A and B, storing the result in the buffer.</li>
    <li><code>consumer()</code>: Retrieves data from the buffer and assembles the resultant matrix.</li>
    <li><code>printTheResultMatrix()</code>: Displays the final resultant matrix after multiplication.</li>
    <li><code>main()</code>: Orchestrates the generation, multiplication, and display of matrices using multiple threads and synchronization mechanisms.</li>
  </ul>
  <li><strong>Struct:</strong></li>
  <ul>
    <li><code>IndexesOfThreadsDate</code>: A custom structure used to hold row, column, and data information for thread communication and avoiding data conflict during matrix multiplication.</li>
  </ul>
</ul>

<h2>Variables and Definitions</h2>
Certainly! Here's an updated version of the HTML-formatted content for the README.md file, including additional details about the variables used in the provided code:

html

<h1>Matrix Multiplication using Producer-Consumer Model</h1>

<p>This C code demonstrates matrix multiplication utilizing a producer-consumer model implemented with pthreads and semaphores.</p>

<h2>Description</h2>

<p>The program generates two random matrices, A and B, and performs matrix multiplication (A * B) using multiple producer threads for computation and a single consumer thread to assemble the resultant matrix.</p>

<h2>Prerequisites</h2>

<p>Ensure you have a C compiler installed to compile and run the code.</p>

<h2>Usage</h2>

<ol>
  <li>Clone the repository or download the C file.</li>
  <li>Compile the code using a C compiler. For example:</li>
</ol>

<pre><code>gcc -o matrix_multiplication matrix_multiplication.c -pthread
</code></pre>

<ol start="3">
  <li>Run the compiled executable:</li>
</ol>

<pre><code>./matrix_multiplication
</code></pre>

<h2>Implementation Details</h2>

<ul>
  <li>The code uses pthreads for creating producer threads to calculate products and a consumer thread to assemble the resulting matrix.</li>
  <li>Semaphore implementation (<code>sem_t</code>) is utilized for synchronization between threads (full, empty, and mutex semaphores).</li>
</ul>

<h2>Variables and Definitions</h2>

<p><code>MIN_ROWS_COLS</code>: Minimum value for rows and columns in the randomly generated matrices.</p>

<p><code>MAX_ROWS_COLS</code>: Maximum value for rows and columns in the randomly generated matrices.</p>

<p><code>MAX_VALUE</code>: Maximum value for each element in the matrices.</p>

<p><code>BUFFER_SIZE</code>: Size of the buffer used in the producer-consumer model.</p>

<p><code>IndexesOfThreadsDate</code>: Custom data structure to avoid data conflict in the product phase.</p>

<p><code>matrixA[MAX_ROWS_COLS][MAX_ROWS_COLS]</code>: Matrix A.</p>

<p><code>matrixB[MAX_ROWS_COLS][MAX_ROWS_COLS]</code>: Matrix B.</p>

<p><code>matrixResult[MAX_ROWS_COLS][MAX_ROWS_COLS]</code>: Resultant matrix (A * B).</p>

<p><code>MatA_Rows</code>: Number of rows in matrix A.</p>

<p><code>MatB_Columns</code>: Number of columns in matrix B.</p>

<p><code>Mat_Brows_Acolumns</code>: Number of rows in matrix B and columns in matrix A (shared rows and columns for the multiplication).</p>

<p><code>ip</code> and <code>ic</code>: Indexes for buffer management.</p>


<h2>How to Use</h2>

<ol>
  <li>The code will generate random matrices A and B with sizes ranging from 3x3 to 6x6.</li>
  <li>It performs matrix multiplication (A * B) using the producer-consumer model.</li>
  <li>The final resultant matrix will be displayed as output.</li>
</ol>


<p>Feel free to modify, enhance, or use it for educational purposes!</p>
